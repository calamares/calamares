#! /bin/sh
#
# SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
# SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Sends a notification to wherever the notifications need to be sent.
#
# Called with the following environment (for tokens / secrets):
#	MATRIX_ROOM
#	MATRIX_TOKEN
#
# Called with the following arguments (in order):
#	- "OK" or "FAIL"
#	- github.workflow
#	- github.repository
#	- github.actor
#	- github.event.ref
#	- commit-message-summary (produced in the workflow)
#	- github.event.compare
#

test -z "$MATRIX_ROOM" && { echo "! No secrets" ; exit 1 ; }
test -z "$MATRIX_TOKEN" && { echo "! No secrets" ; exit 1 ; }

STATUS="$1"

WORKFLOW="$2"
REPOSITORY="$3"
ACTOR="$4"
EVENT="$5"
SUMMARY="$6"
COMPARE="$7"

test "x$STATUS" = "xOK" -o "x$STATUS" = "xFAIL" || { echo "! Invalid status" ; exit 1 ; }

test -z "$WORKFLOW" && { echo "! No event data" ; exit 1 ; }
test -z "$REPOSITORY" && { echo "! No event data" ; exit 1 ; }
test -z "$ACTOR" && { echo "! No event data" ; exit 1 ; }
test -z "$EVENT" && { echo "! No event data" ; exit 1 ; }
# It's ok for summary or the compare URL to be empty

url="https://matrix.org/_matrix/client/r0/rooms/%21${MATRIX_ROOM}/send/m.room.message?access_token=${MATRIX_TOKEN}"
message_data=$(
{
	echo "${STATUS} ${WORKFLOW} in ${REPOSITORY} ${ACTOR} on ${EVENT}"
	test -n "$SUMMARY" && echo ".. ${SUMMARY}"
	test -n "$COMPARE" && echo ".. DIFF ${COMPARE}"
} | jq -Rs '{"msgtype": "m.text", "body":@text}' )

curl -s -XPOST -d "$message_data" "$url" > /dev/null
