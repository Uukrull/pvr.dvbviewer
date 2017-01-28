#pragma once

#ifndef PVR_DVBVIEWER_TIMESHIFTBUFFER_H
#define PVR_DVBVIEWER_TIMESHIFTBUFFER_H

#include "IStreamReader.h"
#include "platform/util/StdString.h"
#include "platform/threads/threads.h"

class TimeshiftBuffer
  : public IStreamReader, public PLATFORM::CThread
{
public:
  TimeshiftBuffer(IStreamReader *strReader, const std::string &bufferPath);
  ~TimeshiftBuffer(void);
  bool IsValid() override;
  ssize_t ReadData(unsigned char *buffer, unsigned int size) override;
  int64_t Seek(long long position, int whence) override;
  int64_t Position() override;
  int64_t Length() override;
  time_t TimeStart() override;
  time_t TimeEnd() override;
  bool NearEnd() override;
  bool IsTimeshifting() override;

private:
  virtual void *Process(void) override;

  CStdString m_bufferPath;
  IStreamReader *m_strReader;
  void *m_filebufferReadHandle;
  void *m_filebufferWriteHandle;
  time_t m_start;
#ifndef TARGET_POSIX
  PLATFORM::CMutex m_mutex;
  uint64_t m_writePos;
#endif
};

#endif
