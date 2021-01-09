// Copyright 2021 Kavykin Andrey Kaviandr@yandex.ru
#include <shared_ptr.h>
template <typename T>
shared_ptr<T>::shared_ptr() : pointer{nullptr}, counter{nullptr} {}
template <typename T>
shared_ptr<T>::shared_ptr(T *ptr) {
  pointer = ptr;
  counter = new std::atomic_uint{1};
}
template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr &r) : counter{nullptr} {
  pointer = r.pointer;
  counter = r.counter;
  (*counter)++;
}
template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr &&r) noexcept : counter{nullptr} {
  pointer = r.pointer;
  counter = r.counter;
  r.pointer = nullptr;
  r.counter = nullptr;
}
template <typename T>
shared_ptr<T>::~shared_ptr() {
  if (!counter) return;
  if (--(*counter) == 0) {
    delete pointer;
    delete counter;
  }
}
template <typename T>
auto shared_ptr<T>::operator=(const shared_ptr &r) -> shared_ptr & {
  if (this == &r) {
    return *this;
  }
  this->shared_ptr();
  pointer = r.pointer;
  counter = r.counter;
  (*counter)++;
  return *this;
}
template <typename T>
auto shared_ptr<T>::operator=(shared_ptr &&r) noexcept -> shared_ptr & {
  if (this == &r) {
    return *this;
  }
  this->shared_ptr();
  pointer = r.pointer;
  counter = r.counter;
  r.pointer = nullptr;
  r.counter = nullptr;
  return *this;
}
template <typename T>
shared_ptr<T>::operator bool() const {
  return pointer != nullptr;
}
template <typename T>
auto shared_ptr<T>::operator*() const -> T & {
  return *pointer;
}
template <typename T>
auto shared_ptr<T>::operator->() const -> T * {
  return pointer;
}
template <typename T>
auto shared_ptr<T>::get() -> T * {
  return pointer;
}

template <typename T>
auto shared_ptr<T>::get_counter() const -> const std::atomic_uint * {
  return counter;
}
template <typename T>
void shared_ptr<T>::reset() {
  *this = std::move(shared_ptr());
}
template <typename T>
void shared_ptr<T>::reset(T *ptr) {
  *this = std::move(shared_ptr<T>(ptr));
}
template <typename T>
void shared_ptr<T>::swap(shared_ptr &r) {
  std::swap(pointer, r.pointer);
  std::swap(counter, r.counter);
}
template <typename T>
auto shared_ptr<T>::use_count() const -> size_t {
  return static_cast<size_t>(*counter);
}