#ifndef E9D70610_1760_4E50_93F3_1129D8E51D1B
#define E9D70610_1760_4E50_93F3_1129D8E51D1B

#include <exception>
#include <optional>

/**
 * @brief Similar to std::optional.
 *
 * A trivially constructible optional value class that can be used as a member of a union.
 * @note std::optional objects cannot be a member of a union.
 * @warning Init() must be called to properly initialize the object before using it.
 */
template <typename T>
class Optional
{
public:
  static_assert(std::is_trivially_constructible_v<T>);

  bool has_value() const
  {
    return initialized_;
  }

  const T& value() const
  {
    if (!initialized_)
    {
      throw std::bad_optional_access();
    }
    return *reinterpret_cast<const T*>(storage);
  }

  Optional<T> operator=(const T& rhs)
  {
    if (initialized_)
    {
      *reinterpret_cast<T*>(storage) = rhs;
    }
    else
    {
      new (static_cast<void*>(storage)) T(rhs);
    }
    initialized_ = true;
    return *this;
  }

  operator std::optional<T>() const
  {
    if (initialized_)
    {
      return std::optional<T>(value());
    }
    else
    {
      return std::optional<T>();
    }
  }

private:
  template <typename U>
  friend void Init(Optional<U>& opt);

  bool initialized_;
  char storage[sizeof(T)];
};

template <typename T>
void Init(Optional<T>& opt)
{
  opt.initialized_ = false;
}

template <typename T>
void Init(Optional<T>& opt, const T& val)
{
  Init(opt);
  opt = val;
}

#endif /* E9D70610_1760_4E50_93F3_1129D8E51D1B */
