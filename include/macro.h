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
}  // namespace macro