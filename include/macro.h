namespace macro {
template <typename T>
constexpr T MAX(T value1, T value2) {
  if (value1 == value2)
    return value1;
  else if (value1 > value2)
    return value1;
  else
    return value2;
}

template <typename T, size_t MAX>
struct ListWithArray
{
  list<T> nodes;
  T storage[MAX];

  void push(T data) {
    auto size_storage = nodes.size();
    this->storage[size_storage] = data;

    nodes.insertBack(&this->storage[size_storage]);
  }
};

}  // namespace macro