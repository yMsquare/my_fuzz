#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include <string>
#include "lib/stringcat.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include <codecvt>
#include <locale>
using namespace fuzztest;

// a test fixture can be created as a default-constructible class
class JsonParseTest {
    //
public:
    void FuzzRapidJson(std::vector<uint8_t> data) {
        // 将字节数据转换为字符串
        std::string jsonString(data.begin(), data.end());

        // 解析 JSON 字符串
        rapidjson::Document d;
        rapidjson::ParseResult result = d.Parse(jsonString.c_str());

        // // 记录解析错误信息（如果有）
        // if (result.IsError()) {
            // 使用 EXPECT 记录解析错误的 JSON 字符串
        EXPECT_FALSE(result.IsError()) << "Parsing failed for JSON: " << jsonString;


        // 使用 StringBuffer 和 Writer 来输出 JSON
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer); // 使用 Writer 来写入数据
    }
    //
private:
    //
};


class StringTest {
public :
    //constructer
    //tear down
    //property function
    void TestCatString(const std::optional<string>& str1, const std::optional<string>& str2) {
    EXPECT_EQ(CatString(str1,str2),str1.value_or("").append(str2.value_or("")));
    }
    void TestReverseString(const std::optional<string>& str){
    string rev = *str;
    std::reverse(rev.begin(),rev.end());
        EXPECT_EQ(ReverseString(str),rev);
    };
    void TestReverseStringWide(const std::optional<string>& str){
        string rev = *str;
        std::reverse(rev.begin(),rev.end());
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide_str = converter.from_bytes(rev);
        std::reverse(wide_str.begin(), wide_str.end());
        rev = converter.to_bytes(wide_str);
        std::reverse(rev.begin(),rev.end());
        EXPECT_EQ(ReverseString(str),rev);
    };

    void TestReverseStringUtf8(const std::optional<string>& str){
        string rev = *str;
        std::reverse(rev.begin(),rev.end());
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide_str = converter.from_bytes(rev);
        std::reverse(wide_str.begin(), wide_str.end());
        rev = converter.to_bytes(wide_str);

        EXPECT_EQ(ReverseString(str),rev)<< "Parsing: " << *str;
    };

};


Domain<std::string> Utf8String() {
    return fuzztest::Map(
        [](const std::vector<uint32_t>& codepoints) {
            std::string result;
            for (uint32_t cp : codepoints) {
                char utf8[4];
                int len = 0;

                if (cp <= 0x7F) {
                    utf8[0] = static_cast<char>(cp);
                    len = 1;
                } else if (cp <= 0x7FF) {
                    utf8[0] = static_cast<char>(0xC0 | (cp >> 6));
                    utf8[1] = static_cast<char>(0x80 | (cp & 0x3F));
                    len = 2;
                } else if (cp <= 0xFFFF) {
                    utf8[0] = static_cast<char>(0xE0 | (cp >> 12));
                    utf8[1] = static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                    utf8[2] = static_cast<char>(0x80 | (cp & 0x3F));
                    len = 3;
                } else if (cp <= 0x10FFFF) {
                    utf8[0] = static_cast<char>(0xF0 | (cp >> 18));
                    utf8[1] = static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
                    utf8[2] = static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                    utf8[3] = static_cast<char>(0x80 | (cp & 0x3F));
                    len = 4;
                }

                result.append(utf8, len);
            }
            return result;
        },
        fuzztest::ContainerOf<std::vector<uint32_t>>(
            fuzztest::InRange<uint32_t>(0, 0x10FFFF)
        )
    );
}


FUZZ_TEST_F(StringTest,TestCatString)
.WithDomains(fuzztest::String(),fuzztest::String());
FUZZ_TEST_F(StringTest,TestReverseString)
.WithDomains(fuzztest::String());
FUZZ_TEST_F(StringTest,TestReverseStringWide)
.WithDomains(Utf8String());
FUZZ_TEST_F(StringTest,TestReverseStringUtf8)
.WithDomains(Utf8String());
FUZZ_TEST_F(JsonParseTest,FuzzRapidJson)
.WithDomains(NonEmpty(Arbitrary<std::vector<uint8_t>>()));