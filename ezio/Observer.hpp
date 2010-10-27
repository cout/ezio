#ifndef ezio__Observer__hpp_
#define ezio__Observer__hpp_

#include <list>

namespace ezio
{

template<typename Event_T>
class Observer;

template<typename Event_T>
class Observable;

template<typename Event_T>
class Observation
{
public:
  Observation();

  typedef std::list<Observer<Event_T> *> Observers;
  typedef std::list<Observable<Event_T> *> Observables;

  void activate(
      Observables::iterator observables_it,
      Observers::iterator observers_it);

  Observables::iterator observables_it() { return observables_it_; }
  Observers::iterator observers_it() { return observers_it_; }

private:
  Observables::iterator observables_it_;
  Observers::iterator observers_it_;
};

template<typename Event_T>
class Observable
{
public:
  Observable();
  virtual ~Observable();

  Observers::iterator add_observer(Observer & observer);
  void remove_observer(Observers::iterator it);

  void notify(Event_T const & event);

private:
  typedef Observation<Event_T>::Observers Observers;
  Observers observers_;
};

template<typename Event_T>
class Observer
{
public:
  Observer();
  virtual ~Observer();

  Observation observe(Observable & observable);
  void unobserve(Observation observation);

  virtual void update(Event_T const & event);

private:
  typedef Observation<Event_T>::Observables Observables;
  Observables observables_;
};

} // namespace ezio

#include "Observer.ipp"

#endif // ezio__Observer__hpp_
