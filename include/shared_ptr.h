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
  auto get_counter() const -> const std::atomic_uint *;
  void reset();
  void reset(T *ptr);
  void swap(shared_ptr &r);
  [[nodiscard]] auto use_count() const -> size_t;
};
#endif  // INCLUDE_SHARED_POINTER_HPP_
