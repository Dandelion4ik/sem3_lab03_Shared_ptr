// Copyright 2021 Kavykin Andrey Kaviandr@yandex.ru
#ifndef INCLUDE_SHARED_POINTER_HPP_
#define INCLUDE_SHARED_POINTER_HPP_
#include <atomic>
#include <iostream>
#include <utility>

template <typename T>
class shared_ptr {
  T *pointer;
  std::atomic_uint *counter;

 public:
  shared_ptr();
  explicit shared_ptr(T *ptr);
  shared_ptr(const shared_ptr &r);
  shared_ptr(shared_ptr &&r) noexcept;
  ~shared_ptr();
  auto operator=(const shared_ptr &r) -> shared_ptr &;
  auto operator=(shared_ptr &&r) noexcept -> shared_ptr &;
  explicit operator bool() const;
  auto operator*() const -> T &;
  auto operator->() const -> T *;
  auto get() -> T *;
  void reset();
  void reset(T *ptr);
  void swap(shared_ptr &r);
  [[nodiscard]] auto use_count() const -> size_t;
};
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
    if (!counter) {
        return;
    }
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
    this->~shared_ptr();
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
    this->~shared_ptr();
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
#endif  // INCLUDE_SHARED_POINTER_HPP_
