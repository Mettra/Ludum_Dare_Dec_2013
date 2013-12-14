template<typename T>
struct BaseType
{
  typedef T type;
};

template<typename T>
struct BaseType<T const>
{
  typedef T type;
};

template<typename T>
struct BaseType<T&>
{
  typedef T type;
};

template<typename T>
struct BaseType<T const &>
{
  typedef T type;
};

template<typename T>
struct BaseType<T *>
{
  typedef T type;
};

template<typename T>
struct BaseType<T const *>
{
  typedef T type;
};

template<typename T>
struct BaseType<T **>
{
  typedef T type;
};

template<typename T>
struct BaseType<T const **>
{
  typedef T type;
};