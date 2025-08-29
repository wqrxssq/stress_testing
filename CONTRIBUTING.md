## Инструкция по добавлению своего языка программирования

Проект написан таким образом, чтобы обеспечить простоту добавления поддержки нового языка

### Начало работы

1) Найдите issue с вашим языком, либо создайте этот issue

2) Сделайте **fork** текущего репозитория и склонируйте его:

    ```bash
    git clone https://github.com/your_nickname/your_repo_name.git
    cd your_repo_name
    ```

Теперь вы готовы вносить изменения.

### Добавление поддержки нового языка

Чтобы ваш стал поддерживаемым, нужно выполнить несколько шагов:

1) Научить `detector` определять ваш язык по расширению файла

2) Добавить компиляцию для вашего языка

3) Написать `*-runner` с примерами генератора, чекера и решений

4) Покрыть тестами написанный вами код

Разберем теперь каждый пункт подробнее:

#### Шаг 1 - Изменение detector

1) Пропишите имя вашего языка в файл `src/langs.hpp`:

    ```cpp
    enum class Language {
        Cxx,
        Python,
        C // эта строчка новая
    };
    ```

2) Добавьте расширения файлов вашего языка в `src/detector/extension-map.cpp`:

    ```cpp
    std::map<std::string, Language> LanguageMapper::extension_map = {
        {".cpp", Language::Cxx},
        {".cc",  Language::Cxx},
        {".py",  Language::Python},
        {".c", Language::C} // Эта строчка новая
        // Расширений для одного языка может быть несколько
    };
    ```

#### Шаг 2 - Написание класса для компиляции

**Примечание**: Если ваш язык интерпритируемый, то этапом компиляции будем называть создание `bash`-скрипта, по которому будет исполнятся ваш код. (для подробностей смотрите реализацию для `Python`)

1) Добавьте в `src/compiler-builder/language-compilers.hpp` класс для компилятора вашего языка наследуясь от `LanguageCompiler`:

    Пример для языка `C`:

    ```cpp
    class CCompiler final : public LanguageCompiler {
       public:
        bool Compile(const std::string& file_path, const std::string& bin_path) const override;
    };
    ```

2) Создайте файл `<your_lang_name>-compiler.cpp` в папке `src/compiler-builder`:

    Пример для языка `C`:

    ```cpp
    #include <cstdlib>
    #include <string>

    #include "language-compilers.hpp"

    bool CCompiler::Compile(const std::string& file_path, const std::string& bin_path) const {
        std::string cmd = "gcc " + file_path + " -o " + bin_path;
        return system(cmd.c_str()) == 0;
    }
    ```

    После чего добавьте ваш файл в `CMakeLists.txt`:

    ```cmake
    add_library(${PROJECT_NAME}_objs OBJECT
        ...

        src/compiler-builder/language-compilers.hpp
        src/compiler-builder/py-compiler.cpp
        src/compiler-builder/cpp-compiler.cpp
        src/compiler-builder/c-compiler.cpp # Эта строчка новая

        ...
    )
    ```

3) Добавьте в `src/detector/compiler-factory.cpp` ваш класс, если `detector` определил ваш язык:

    Пример для языка `C`:

    ```cpp
    switch (lang) {
        case Language::Cxx:
            return std::make_unique<CppCompiler>();
        case Language::Python:
            return std::make_unique<PyCompiler>();
        case Language::C: // эта строчка новая
            return std::make_unique<CCompiler>(); // эта строчка новая
    }
    ```

Готово! На данном этапе проект уже поддерживает новый язык! Можете попробовать сделать сборку через `make build`

#### Шаг 3 - Написание примеров

Создайте папку `<your_lang_name>-runner` в `src`, вам предстоит написать 4 файла на вашем языке для решения [задачи из примера](example_task.md):

- `generator.*`
- `naive-solution.*`
- `smart-solution.*`
- `advanced-cheker.*`

Не бойтесь подглядывать в уже написанные `*-runner` для других языков.

Также добавьте поддержку языка в makefile:

Пример для `C`:

```makefile
else ifeq ($(RUN_LANG),c)
 NAIVE     ?= src/c-runner/naive-solution.c
 SMART     ?= src/c-runner/smart-solution.c
 GENERATOR ?= src/c-runner/generator.c
 CHECKER   ?= src/c-runner/advanced-checker.c
```

На данном этапе уже можно проверить, как все работает, должна работать вся функциональность из README и для вашего языка.

#### Шаг 4 - Покрытие тестами

Чтобы мы знали, что ваша функциональность действительно работает, нужно покрывать все тестами:

1) Написать тест в `unittests/test-language-mapper.cpp` для проверки, что `detector` может определить ваш язык:

    Пример для `C`:

    ```cpp
    TEST(TestLanguageMapper, TestCExtension) {
        std::string ext = ".c";
        EXPECT_EQ(LanguageMapper::FromExtension(ext), Language::C);

        std::string path = "/bar/foo/generator.c";
        EXPECT_EQ(LanguageMapper::FromPath(path), Language::C);
    }
    ```

2) Написать тест в `unittests/test-compiler-factory.cpp` для проверки, назначается ли ваш компилятор:

    Пример для `C`:

    ```cpp
    TEST(TestCompilerFactory, TestCPath) {
        std::string path_to_file = "src/cpp-runner/generator.c";
        auto compiler_ptr = CompilerFactory::FromPath(path_to_file);
        auto& compiler = *compiler_ptr;
        EXPECT_EQ(typeid(compiler), typeid(CCompiler));
    }
    ```

### Завершение

Обновите `README` (добавьте новый язык).

Оформите `PR` с описанием: что добавлено, какие команды запускать, какие зависимости нужны.
