#include <stdio.h>
#include "gtest/gtest.h"

extern "C" {
#include "strbuilder.h"
}

TEST (StringBuilderTest, AppendOneString_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 1024);

   const char *expected = "Hello, World!";

   str_builder_append(&cmd, expected);

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, AppendOneStringToEnd_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *expected = "1234567890123456";

   str_builder_append(&cmd, expected);

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, AppendTwoStrings_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *in1 = "Hello, ";
   const char *in2 = "World!";
   const char *expected = "Hello, World!";

   str_builder_append(&cmd, in1);
   str_builder_append(&cmd, in2);

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, SprintfOneInt_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *expected = "10";

   str_builder_sprintf(&cmd, "%d", 10);

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, SprintfTwoInts_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *expected = "10 25";

   str_builder_sprintf(&cmd, "%d %d", 10, 25);

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, SprintfLargeBuffer_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *expected = "10 25 1.53 Hello, World!";

   str_builder_sprintf(&cmd, "%d %d %0.2f %s", 10, 25, 1.53, "Hello, World!");

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, SprintfReallyLongString_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *expected = "sajdasjdosiadcmaisdcmas98mcd98sa cd98ascdhasdcas hcdyu ahugdcawgd78awgd7w ycdwacdhwaudh w8ahcd8awodcwaocdoawpcdoaw87hd87wahdc78wcdwahdcuwhacdwhaduihawdawucdhwahcduiahac";

   str_builder_append(&cmd, expected);

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}


TEST (StringBuilderTest, SprintfTwice_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *expected = "1025";

   str_builder_sprintf(&cmd, "%d", 10);
   str_builder_sprintf(&cmd, "%d", 25);

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, NAppend_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 4);

   const char *expected = "12345678";

   str_builder_nappend( &cmd, "1234567890", 8 );

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

TEST (StringBuilderTest, SprintfLots_CheckOutputEqualsInput)
{
   str_builder_t cmd;
   str_builder_init(&cmd, 16);

   const char *expected = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin auctor viverra risus, sed aliquam nibh sodales sed. Donec eget orci vitae odio elementum vestibulum. Nam sit amet tempus neque. Fusce elementum nunc nec dui elementum fringilla. Nunc ac viverra mi. Phasellus eget dolor eget libero consequat gravida. Duis sed molestie ex, sit amet interdum massa. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Donec ac ex sed massa placerat efficitur ut sed nunc. Aliquam eu dolor risus. Duis ex metus, porttitor eget nisi ut, sagittis bibendum nisi. Quisque nec ligula sodales, egestas quam non, mollis mi.Aenean commodo turpis et posuere tincidunt. Mauris a sem sed justo imperdiet mattis. Quisque rutrum risus semper diam hendrerit lobortis. Cras purus nisi, faucibus in orci a, egestas aliquam justo. Quisque ex turpis, suscipit faucibus posuere quis, pellentesque non lorem. Aliquam in dapibus lorem. Curabitur convallis, est quis rutrum laoreet, justo orci sollicitudin ipsum, vitae mollis urna libero vel enim. Curabitur aliquam fringilla eleifend.Vivamus sed auctor enim, eu accumsan arcu. Donec vitae tellus quis neque aliquam iaculis sit amet ac felis. Donec fermentum lectus nibh, at interdum eros tincidunt pulvinar. Nunc sed quam metus. Sed et finibus mi. Morbi a rutrum odio. Mauris dapibus, dui ac mattis rhoncus, nulla quam aliquam ex, sed mollis augue dui et leo. Nulla facilisi. Nullam tempor iaculis nunc, a pulvinar mi aliquam eget. Morbi tincidunt blandit tellus in aliquet. Ut vel velit sit amet lorem finibus lacinia.";

   str_builder_sprintf(&cmd, "%s", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin auctor viverra risus, sed aliquam nibh sodales sed. Donec eget orci vitae odio elementum vestibulum. Nam sit amet tempus neque. Fusce elementum nunc nec dui elementum fringilla. Nunc ac viverra mi. Phasellus eget dolor eget libero consequat gravida. Duis sed molestie ex, sit amet interdum massa. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Donec ac ex sed massa placerat efficitur ut sed nunc. Aliquam eu dolor risus. Duis ex metus, porttitor eget nisi ut, sagittis bibendum nisi. Quisque nec ligula sodales, egestas quam non, mollis mi.");
   str_builder_sprintf(&cmd, "%s", "Aenean commodo turpis et posuere tincidunt. Mauris a sem sed justo imperdiet mattis. Quisque rutrum risus semper diam hendrerit lobortis. Cras purus nisi, faucibus in orci a, egestas aliquam justo. Quisque ex turpis, suscipit faucibus posuere quis, pellentesque non lorem. Aliquam in dapibus lorem. Curabitur convallis, est quis rutrum laoreet, justo orci sollicitudin ipsum, vitae mollis urna libero vel enim. Curabitur aliquam fringilla eleifend.");
   str_builder_append(&cmd, "Vivamus sed auctor enim, eu accumsan arcu. Donec vitae tellus quis neque aliquam iaculis sit amet ac felis. Donec fermentum lectus nibh, at interdum eros tincidunt pulvinar. Nunc sed quam metus. Sed et finibus mi. Morbi a rutrum odio. Mauris dapibus, dui ac mattis rhoncus, nulla quam aliquam ex, sed mollis augue dui et leo. Nulla facilisi. Nullam tempor iaculis nunc, a pulvinar mi aliquam eget. Morbi tincidunt blandit tellus in aliquet. Ut vel velit sit amet lorem finibus lacinia.");

   char *result = str_builder_get(&cmd);
   int len = str_builder_size(&cmd);

   puts(result);

   ASSERT_EQ( len, strlen(expected) ) << "The length of the resulting string in unexpected";
   ASSERT_EQ( result[len], '\0' ) << "There is no termintating null-character";
   ASSERT_STREQ( result, expected ) << "The content of the resulting is unexpected";

   str_builder_free(&cmd);
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}




