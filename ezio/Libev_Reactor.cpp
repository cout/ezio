#include "Libev_Reactor.hpp"

#include <stdexcept>
#include <memory>

extern "C"
void
ezio_libev_file_callback(EV_P_ ev_io * io, int revents);

extern "C"
void
ezio_libev_timer_callback(EV_P_ ev_timer * timer, int revents);

namespace ezio
{

namespace
{

struct Libev_Io_Watcher
{
  Libev_Io_Watcher(File & file, Reactor::File_Callback & callback, int revents)
    : file_(file)
    , callback_(callback)
  {
    ev_io_init(&io_, ezio_libev_file_callback, file.fd(), revents);
    io_.data = this;
  }

  void start(struct ev_loop * loop)
  {
    ev_io_start(loop, &io_);
  }

  void stop(struct ev_loop * loop)
  {
    ev_io_stop(loop, &io_);
  }

  static Libev_Io_Watcher * from_ev_io(ev_io * io)
  {
    return static_cast<Libev_Io_Watcher *>(io->data);
  }

  File file_;
  Reactor::File_Callback & callback_;
  ev_io io_;
};

struct Libev_Timer_Watcher
{
  Libev_Timer_Watcher(Reactor::Timer_Callback & callback, Time_Value start, Time_Value delay)
    : callback_(callback)
  {
    ev_timer_init(&timer_, ezio_libev_timer_callback, start.as_double(), delay.as_double());
    timer_.data = this;
  }

  void start(struct ev_loop * loop)
  {
    ev_timer_start(loop, &timer_);
  }

  void stop(struct ev_loop * loop)
  {
    ev_timer_stop(loop, &timer_);
  }

  static Libev_Timer_Watcher * from_ev_timer(ev_timer * timer)
  {
    return static_cast<Libev_Timer_Watcher *>(timer->data);
  }

  Reactor::Timer_Callback & callback_;
  ev_timer timer_;
};

int libev_event_type(ezio::File_Event file_event)
{
  int revents = 0;

  if (file_event.read())
  {
    revents |= EV_READ;
  }

  if (file_event.write())
  {
    revents |= EV_WRITE;
  }

  return revents;
}

File_Event ezio_event_type(int ev_event)
{
  return File_Event(
      (ev_event & EV_READ)  ? File_Event::READ  : File_Event::NONE,
      (ev_event & EV_WRITE) ? File_Event::WRITE : File_Event::NONE);
}

} // namespace

} // ezio

extern "C"
void
ezio_libev_file_callback(EV_P_ ev_io * io, int revents)
{
  ezio::Libev_Io_Watcher * watcher = ezio::Libev_Io_Watcher::from_ev_io(io);
  watcher->callback_(watcher->file_, ezio::ezio_event_type(revents));
}

extern "C"
void
ezio_libev_timer_callback(EV_P_ ev_timer * timer, int revents)
{
  ezio::Libev_Timer_Watcher * watcher = ezio::Libev_Timer_Watcher::from_ev_timer(timer);
  watcher->callback_();
}

ezio::Libev_Reactor::
Libev_Reactor()
  : loop_(ev_default_loop(EVFLAG_AUTO)) // TODO: support more than one event loop per app
{
}

namespace
{

} // namespace

void
ezio::Libev_Reactor::
run()
{
  ev_loop(loop_, 0);
}

void
ezio::Libev_Reactor::
stop()
{
  ev_unloop(loop_, EVUNLOOP_ALL);
}

void *
ezio::Libev_Reactor::
io_add(
    File & file,
    File_Callback & file_callback,
    File_Event file_event)
{
  int revents = libev_event_type(file_event);

  std::auto_ptr<Libev_Io_Watcher> watcher(
      new Libev_Io_Watcher(file, file_callback, revents));
  watcher->start(loop_);

  void * key = static_cast<void *>(watcher.get());
  watcher.release();
  return key;
}

void
ezio::Libev_Reactor::
io_remove(
    void * key)
{
  Libev_Io_Watcher * watcher = static_cast<Libev_Io_Watcher *>(key);
  watcher->stop(loop_);
  delete watcher;
}

void *
ezio::Libev_Reactor::
timer_add(
    Timer_Callback & timer_callback,
    Time_Value delay,
    Time_Value repeat)
{
  std::auto_ptr<Libev_Timer_Watcher> watcher(
      new Libev_Timer_Watcher(timer_callback, delay, repeat));
  watcher->start(loop_);

  void * key = static_cast<void *>(watcher.get());
  watcher.release();
  return key;
}

void
ezio::Libev_Reactor::
forked(PID pid)
{
  ev_child cw;

  if (pid == 0)
  {
    // child
    ev_loop_fork(loop_);

    // TODO: how to inform other reactor loops about the child?
  }
  else
  {
    // parent

    // TODO: do we care about getting a callback when the child exits?
  }
}

