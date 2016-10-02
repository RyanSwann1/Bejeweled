#pragma once

#include <unordered_map>
#include <string>

template <class T>
class ResourceManager
{
public:
	ResourceManager() {}
	virtual ~ResourceManager() {}

	bool requireResource(const std::string& id)
	{
		auto res = find(id);
		if (res)
		{
			res->second++;
			return true;
		}

		T* resource = loadFromFile(id);
		if (resource)
		{
			m_resources.emplace(id, std::make_pair(resource, 1));
			return true;
		}
		
		return false;
	}

	T* getResource(const std::string& id)
	{
		auto res = find(id);
		return (res ? res->first : nullptr);
	}

	void releaseResource(const std::string& id)
	{
		auto res = find(id);
		if (res)
		{
			res.second--;
		}
		if (res.second == 0)
		{
			removeResource(id);
		}
	}

protected:
	std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
	std::unordered_map<std::string, std::string> m_filePaths;
	virtual T* loadFromFile(const std::string& id) = 0;
	virtual void loadInResources(const std::string& fileName) = 0;

	void purgeResources()
	{
		for (auto &i : m_resources)
		{
			delete i.second.first;
		}
		m_resources.clear();
	}
private:

	std::pair<T*, unsigned int>* find(const std::string& id)
	{
		auto iter = m_resources.find(id);
		return (iter != m_resources.cend() ? &iter->second : nullptr);
	}

	void removeResource(const std::string& id)
	{
		auto res = m_resources.find(id);
		if (res)
		{
			delete res.second.first;
			m_resources.erase(res);
		}
	}


};

