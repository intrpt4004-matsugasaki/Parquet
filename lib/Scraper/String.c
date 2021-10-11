#include "Scraper/String.h"

static uint8_t *GetPrimitive(String_t *str) {
	return strdup(str->_String);
}

static uint32_t GetLength(String_t *str) {
	return strlen(str->_String);
}

static uint8_t GetCharAt(String_t *str, const uint32_t index) {
	if (String.GetLength(str) < index) {
		Error.Panic(u8"\e[32m", u8"String#GetCharAt");
	}

	return String.GetPrimitive(str)[index];
}

static uint8_t GetHeadChar(String_t *str) {
	if (String.GetLength(str) < 1) {
		Error.Panic(u8"\e[32m", u8"String#GetHeadChar");
	}

	return String.GetCharAt(str, 0);
}

static String_t *Substring(String_t *str, const uint32_t beginIndex, const uint32_t lastIndex) {
	if (   String.GetLength(str) + 1 < beginIndex
		|| String.GetLength(str) + 1 < lastIndex
		|| beginIndex > lastIndex ) {
			Error.Panic(u8"\e[32m", u8"String#Substring");
		}

	if (beginIndex == lastIndex) return String.New(u8"");

	uint8_t *s = (uint8_t *)(
		calloc(1 + lastIndex - beginIndex, sizeof(uint8_t))
	);
	strncpy(s, str->_String + beginIndex, lastIndex - beginIndex);
	s[lastIndex - beginIndex - 1] = String.NUL;

	return String.New(s);
}

static String_t *Concat(String_t *str, String_t *anString) {
	uint8_t *s = (uint8_t *)(
		Memory.CountedAllocate(String.GetLength(str) + String.GetLength(anString) + 1, sizeof(uint8_t))
	);

	strncpy(s, String.GetPrimitive(str), String.GetLength(str));
	strncat(s, String.GetPrimitive(anString), String.GetLength(anString));

	return String.New(s);
}

static String_t *Copy(String_t *s) {
	return String.New(String.GetPrimitive(s));
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
		return false;

	for (uint32_t i = 0; i < String.GetLength(prefix); i++)
		if (String.GetCharAt(str, i) != String.GetCharAt(prefix, i))
			return false;

	return true;
}

static bool StartsWithChar(String_t *str, const uint8_t ch) {
	return String.GetHeadChar(str) == ch;
}

static void Delete(String_t *str) {
	Memory.Free(str->_String);
	Memory.Free(str);
}

static String_t *New(const uint8_t *string) {
	String_t *str = (String_t *)(Memory.Allocate(sizeof(String_t)));

	str->_Size					= (string != NULL)? strlen(string) + 1 : 1;
	str->_String				= (uint8_t *)(
		Memory.CountedAllocate(str->_Size, sizeof(uint8_t))
	);
	if (string != NULL) strncpy(str->_String, string, strlen(string));
	str->_String[(string != NULL)? str->_Size - 1 : 0] = String.NUL;

	str->GetPrimitive			= GetPrimitive;
	str->GetLength				= GetLength;
	str->GetCharAt				= GetCharAt;
	str->GetHeadChar			= GetHeadChar;
	str->Substring				= Substring;
	str->Concat					= Concat;
	str->Copy					= Copy;
	str->IsEmpty				= IsEmpty;
	str->Equals					= Equals;
	str->StartsWith				= StartsWith;
	str->StartsWithChar			= StartsWithChar;
	str->Delete					= Delete;

	return str;
}

static String_t *FromChar(const uint8_t ch) {
	uint8_t tmp[] = { ch };
	return String.New(tmp);
}

static String_t *FromFile(const uint8_t *path) {
	FILE *file;
	if ((file = fopen(path, "r")) == NULL)
		Error.Panic(u8"\e[32m", u8"file open failed.\n");

	String_t *text = String.New(u8"");

	int8_t c;
	while ((c = fgetc(file)) != EOF)
		text = String.Concat(text, String.FromChar(c));

	fclose(file);

	return text;
}

_String String = {
	.NUL						= '\0',

	.New						= New,
	.FromChar					= FromChar,
	.FromFile					= FromFile,
	.Delete						= Delete,

	.GetPrimitive				= GetPrimitive,
	.GetLength					= GetLength,
	.GetCharAt					= GetCharAt,
	.GetHeadChar				= GetHeadChar,
	.Substring					= Substring,
	.Concat						= Concat,
	.Copy						= Copy,
	.IsEmpty					= IsEmpty,
	.Equals						= Equals,
	.StartsWith					= StartsWith,
	.StartsWithChar				= StartsWithChar,
};
