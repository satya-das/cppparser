// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A06AFF15_7A57_4160_9AB3_EE13CF751B6F
#define A06AFF15_7A57_4160_9AB3_EE13CF751B6F

#include <cppast/cpp_compound.h>

#include <functional>
#include <memory>

namespace cppparser {

/**
 * @brief Parses C++ source and generates an AST.
 *
 * @warning Although its a class it is not reentrant because underlying btyacc is not reentrant.
 * So, any change done through this class is global and affects the result of other instances too.
 */
class CppParser
{
public:
  using ErrorHandler =
    std::function<void(const char* errLineText, size_t lineNum, size_t errorStartPos, int lexerContext)>;

public:
  void addKnownMacro(std::string knownMacro);
  void addKnownMacros(const std::vector<std::string>& knownMacros);

  void addDefinedName(std::string definedName, int value = 0);

  void addUndefinedName(std::string undefinedName);
  void addUndefinedNames(const std::vector<std::string>& undefinedNames);

  void addIgnorableMacro(std::string ignorableMacro);
  void addIgnorableMacros(const std::vector<std::string>& ignorableMacros);

  void addKnownApiDecor(std::string knownApiDecor);
  void addKnownApiDecors(const std::vector<std::string>& knownApiDecor);

  bool addRenamedKeyword(const std::string& keyword, std::string renamedKeyword);

  void parseEnumBodyAsBlob();
  void parseFunctionBodyAsBlob(bool asBlob);

public:
  std::unique_ptr<cppast::CppCompound> parseFile(const std::string& filename);
  std::unique_ptr<cppast::CppCompound> parseStream(char* stm, size_t stmSize);

  void setErrorHandler(ErrorHandler errorHandler);
  void resetErrorHandler();
};

} // namespace cppparser

#endif /* A06AFF15_7A57_4160_9AB3_EE13CF751B6F */
