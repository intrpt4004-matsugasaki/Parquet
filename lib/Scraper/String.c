#include "Scraper/String.h"

static uint8_t *GetPrimitive(String_t *str) {
	return str->_String;
}

static uint32_t GetLength(String_t *str) {
	return strlen(str->_String);
}

static uint8_t GetCharAt(String_t *str, const uint32_t index) {
	if (String.GetLength(str) < index) {
		Error.Panic(u8"\e[34m", u8"String#GetCharAt");
	}

	return String.GetPrimitive(str)[index];
}

static uint8_t GetHeadChar(String_t *str) {
	if (String.GetLength(str) < 1) {
		Error.Panic(u8"\e[34m", u8"String#GetHeadChar");
	}

	return String.GetCharAt(str, 0);
}

static String_t *Substring(String_t *str, const uint32_t beginIndex, const uint32_t lastIndex) {
	if (   String.GetLength(str) + 1 < beginIndex
		|| String.GetLength(str) + 1 < lastIndex
		|| beginIndex > lastIndex ) {
			Error.Panic(u8"\e[34m", u8"String#Substring");
		}

	uint8_t *s = (uint8_t *)(
		calloc(1 + lastIndex - beginIndex, sizeof(uint8_t))
	);
	strncpy(s, str->_String + beginIndex, lastIndex - beginIndex);
	s[lastIndex - beginIndex - 1] = String.NUL;

	return String.New(s);
}

static bool IsEmpty(String_t *str) {
	return String.GetLength(str) == 0;
}

static bool Equals(String_t *str, String_t *anString) {
	return !strncmp(
		String.GetPrimitive(str),
		String.GetPrimitive(anString),
		(String.GetLength(str) >= String.GetLength(anString))?
			String.GetLength(str) : String.GetLength(anString)
	) == 1;
}

static bool StartsWith(String_t *str, String_t *prefix) {
	if (String.GetLength(str) < String.GetLength(prefix))
		Error.Panic(u8"\e[34m", u8"String#StartsWith");

	for (uint32_t i = 0; i < String.GetLength(prefix); i++)
		if (String.GetCharAt(str, i) != String.GetCharAt(prefix, i))
			return false;

	return true;
}

static bool StartsWithChar(String_t *str, const uint8_t ch) {
	return String.GetHeadChar(str) == ch;
}

static String_t *New(const uint8_t *string) {
	String_t *str = (String_t *)(Memory.Allocate(sizeof(String_t)));

	str->_Size					= (string != NULL)? strlen(string) + 1 : 1;
	str->_String				= (uint8_t *)(calloc(str->_Size, sizeof(uint8_t)));
	if (string != NULL) strncpy(str->_String, string, strlen(string));
	str->_String[(string != NULL)? str->_Size - 1 : 0] = String.NUL;

	str->GetPrimitive			= GetPrimitive;
	str->GetLength				= GetLength;
	str->GetCharAt				= GetCharAt;
	str->GetHeadChar			= GetHeadChar;
	str->Substring				= Substring;
	str->IsEmpty				= IsEmpty;
	str->Equals					= Equals;
	str->StartsWith				= StartsWith;
	str->StartsWithChar			= StartsWithChar;

	return str;
}

static void Delete(String_t *str) {
	Memory.Delete(str);
}

_String String = {
	.NUL								= '\0',

	.New								= New,
	.Delete								= Delete,

	.GetPrimitive						= GetPrimitive,
	.GetLength							= GetLength,
	.GetCharAt							= GetCharAt,
	.GetHeadChar						= GetHeadChar,
	.Substring							= Substring,
	.IsEmpty							= IsEmpty,
	.Equals								= Equals,
	.StartsWith							= StartsWith,
	.StartsWithChar						= StartsWithChar,
};
