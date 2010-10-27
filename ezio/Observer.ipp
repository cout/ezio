#include "Observer.hpp"

template<typename Event_T>
ezio::Observation<Event_T>::
Observation()
  : observables_it_()
  , observers_it_()
{
}

template<typename Event_T>
ezio::Observation<Event_T>::
activate(
    Observables::iterator observables_it,
    Observers::iterator observers_it)
{
  observables_it_ = observables_it;
  observers_it_ = observers_it;
}

template<typename Event_T>
ezio::Observable<Event_T>::
Observable()
{
}

template<typename Event_T>
ezio::Observable<Event_T>::
~Observable()
{
  // TODO
}

template<typename Event_T>
Observers::iterator
ezio::Observable<Event_T>::
add_observer(Observer<Event_T> & observer);
{
  Observers::iterator it(observers_.insert(
          observes_.end(),
          &observer));

  return it;
}

template<typename Event_T>
void
ezio::Observable<Event_T>::
remove_observer(Observers::iterator it)
{
  observers_.erase(it);
}

template<typename Event_T>
void
ezio::Observable<Event_T>::
notify(Event_T const & event)
{
  Observers::iterator it(observers_.begin());
  Observers::iterator end(observers_.end());

  for(; it != end; ++it)
  {
    it->update(event);
  }
}

template<typename Event_T>
ezio::Observer<Event_T>::
Observer()
  : observed_()
{
}

template<typename Event_T>
ezio::Observer<Event_T>::
~Observer()
{
  Observables::iterator it(observed_.begin());
  Observables::iterator end(observed_.end());

  for(; it != end; ++it)
  {
    observed_->remove_observer(*it);
  }
}

template<typename Event_T>
ezio::Observation<Event_T>
ezio::Observer<Event_T>::
observe(Observable<Event_T> & observable)
{
  // Create a temporary list so we can get an iterator
  Observables tmp;
  tmp.push_back(&observable);

  // Construct the observation
  Observation<Event_T> observation;

  // Add the observer to the observable
  observable.add_observer(observation);

  // Now splice the temporary list into our list of observables.  It is
  // important that this step doesn't throw, because at this point we've
  // already modified the observable.
  observables_.splice(observables_.end(), tmp);

  return observation;
}

template<typename Event_T>
void
ezio::Observer<Event_T>::
unobserve(Observation<Event_T> observation)
{
  observable.remove_observer(observation.observers_it());
  observables_.erase(observation.observables_it());
}

template<typename Event_T>
void
ezio::Observer<Event_T>::
update(Event_T const & /* event */)
{
}

