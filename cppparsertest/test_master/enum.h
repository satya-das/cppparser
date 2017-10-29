enum Enum
{
	kItem1,
	kItem2 = 4,
	kItem3,
};

enum Enum
{
	kItem1,
	kItem2 = 4,
	kItem3,
};

enum Enum
{
	kItem1,
  // Testing
	kItem2 = 4,
	kItem3,
  // Tested
};

enum class Enum
{
	kItem1,
	kItem2 = 4,
	kItem3,
};

enum Enum : std::uint32_t
{
	kItem1,
  // Testing
	kItem2 = 4,
	kItem3,
  // Tested
};

enum class Enum : std::uint32_t
{
	kItem1,
  // Testing
	kItem2 = 4,
	kItem3,
  // Tested
};

enum Enum : std::uint32_t;

enum class Enum : std::uint32_t;

enum class Enum;
