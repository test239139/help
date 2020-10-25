#include <stdio.h>
#include <ctype.h>

// ищем самое первое слово в строке
int FindFirstWord(char* text, char** begin, char** end)
{
    for (; *text && !isalpha(*text); ++text) { ; }   // int isalpha(int c) проверяет, является ли передаваемый символ алфавитным

    *begin = text;

    for (; *text && isalpha(*text); ++text) { ; }

    *end = text;

    return (*begin != *end);
}

// двигаем строку
char* PullUpSubstr(char* text, size_t length)
{
    for (; *text; *text = *(text + length), ++text) { ; }

    return text;
}

// сравниваем 2 строки (последовательности)
int CompareSequence(char* first, char* second, size_t length)
{
    for (; *first && *second && length && (*first == *second); ++first, ++second, --length) { ; }

    return (length == 0);
}

// копируем 2 последовательности
char* CopySequence(char* dist, const char* source, size_t length)
{
    for (; *source && length; *dist++ = *source++, --length) { ; }

    return dist;
}

// ищем дубль слово, если нашли, то возвращаем указатель, иначе ноль
char* GetDuplicateWord(char* text, char* word, size_t length)
{
    char* duplicate = NULL;

    char* begin;
    char* end;
    for (; !duplicate && FindFirstWord(text, &begin, &end); text = end + 1)
    {
        if (((end - begin) == length) && CompareSequence(begin, word, length))
        {
            duplicate = begin;
        }
    }

    return duplicate;
}
//----------------------------------------------//
// удаление всех дубль слов
size_t DeleteDuplicate(char* text, char* result)
{
    size_t count = 0;

    char* begin;
    char* end;
    char* cursor;
    int find;

    for (; FindFirstWord(text, &begin, &end); text = end + 1)
    {
        for (cursor = end + 1, find = 0; (cursor = GetDuplicateWord(cursor, begin, end - begin)) != NULL; ++find)
        {
            PullUpSubstr(cursor, end - begin);
        }

        if (find)
        {
            result = CopySequence(result, begin, end - begin);
            *result++ = ' ';
            *result = 0;

            PullUpSubstr(begin, end - begin);
            end = begin;
            count++;
        }
    }

    return count;
}

int main()
{
    printf("Vvedite text (english): ");
    char text[1024];
    fgets(text, sizeof(text) - 1, stdin);

    char result[1024] = { 0 };
    size_t count = DeleteDuplicate(text, result);

    printf("%s%s%u\n", text, result, count);

    return 0;
}
