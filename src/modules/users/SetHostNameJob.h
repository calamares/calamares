/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  Rohan Garg <rohan@kde.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef SETHOSTNAMEJOB_CPP_H
#define SETHOSTNAMEJOB_CPP_H

#include <Job.h>

class SetHostNameJob : public Calamares::Job
{
      Q_OBJECT
public:
    SetHostNameJob(const QString &hostname);
    QString prettyName() const override;
    Calamares::JobResult exec() override;
private:
  const QString m_hostname;
};


#endif // SETHOSTNAMEJOB_CPP_H
