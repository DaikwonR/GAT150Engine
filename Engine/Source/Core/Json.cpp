#include "Json.h"
#include "EFile.h"

#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace Json
{
	bool Json::Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!File::ReadFile(filename, buffer))
		{
			return false;
		}

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		document.ParseStream(istream);
		if (!document.IsObject())
		{
			std::cerr << "Could not parse Json: " << filename << std::endl;
			return false;
		}

		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
		{
			if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
			return false;
		}

		data = value[name.c_str()].GetString();

		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired)
	{
		return false;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Color& data, bool isRequired)
	{
		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
		{
			if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
			return false;
		}

		data = value[name.c_str()].GetInt();

		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
		{
			if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
			return false;
		}

		data = value[name.c_str()].GetFloat();

		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
		{
			if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
			return false;
		}

		data = value[name.c_str()].GetBool();

		return true;
	}

}

