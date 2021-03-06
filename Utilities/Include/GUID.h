#ifndef _UTILZ_GUID_H_
#define _UTILZ_GUID_H_
#include "CompileTimeString.h"
#include <string>

namespace Utilities
{
	struct GUID
	{
		struct Compare
		{
			inline bool operator() (const GUID& lhs, const GUID& rhs) const
			{
				return lhs.id < rhs.id;
			}
		};

		struct Hasher
		{
			inline HashValue operator()(const GUID& g) const
			{
				return g.id;
			}
		};


		GUID() : id(0) {};
		GUID(HashValue idi) : id(idi) { };
		GUID(const std::string& str) : id(StringHash::GetHash_ConstexprString(str.c_str(), uint32_t(str.size()))) { };
		template<std::size_t N>
		constexpr GUID(const char(&a)[N]) : id(StringHash::GetHash_ConstexprString(a, N - 1)) { };
		GUID(const GUID& other) : id(other.id) {}
		GUID(const GUID&& other) : id(other.id) {}
		bool operator!=(const GUID& other) const { return id != other.id; }
		bool operator==(const GUID& other) const { return id == other.id; }
		GUID& operator=(const GUID& other) { this->id = other.id; return *this; }
		constexpr operator HashValue() { return id; };
		GUID operator+(const GUID &other) const
		{
			return id ^ other.id;
		}
		HashValue id;
	};


}


#endif //SE_UTILZ_GUID_H_