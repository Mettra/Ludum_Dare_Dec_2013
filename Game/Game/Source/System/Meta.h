#include <string>
#include <map>
#include "BaseType.h"

class Variant
{
public:
  template <typename T>
  Variant(T data) :data(&data),TypeName(typeid(T).name()),BaseTypeName(typeid(BaseType<T>::type).name())
  {

  }


private:
  void *data;
  const char *TypeName;
  const char *BaseTypeName;
};

template<typename Class>
class MetaData
{
public:
  MetaData() {}

  void Init(std::string name)
  {
    this->name = name;
  }

  std::string const &Name() const { return name; }

  void AddMember(std::string const &name,unsigned offset)
  {
    members.insert(std::make_pair(name,offset));
  }

  unsigned GetMember(std::string const &name)
  {
    auto it = members.find(name);
    if(it == members.end())
      return (unsigned)(-1);

    return it->second;
  }

private:
  std::string name;
  std::map<std::string,unsigned> members;
};

template<typename Class>
class MetaRegister
{
public:
  MetaRegister(std::string name)
  {
    GetMeta()->Init(name);
    RegisterMetaData();
  }
  
  void RegisterMetaData();

  void AddMember(std::string const &name,unsigned offset)
  {
    GetMeta()->AddMember(name,offset);
  }

  static MetaData<Class> *GetMeta()
  {
    static MetaData<Class> meta;
    return &meta;
  }

  Class *NullCast()
  {
    return (Class *)0;
  }
};


template<typename Class>
class MetaInterface
{
public:
  MetaInterface()
  {
    GetMeta()->Init(typeid(Class).name());
  }

  void AddMember(std::string const &name,void *data)
  {
    virtualMembers.insert(std::make_pair(name,data));
  }

  template<typename T>
  T& GetMember(std::string const &name)
  {
    unsigned offset = GetMeta()->GetMember(name);
    if(offset == (unsigned)(-1))
    {
      return *(T *)virtualMembers.find(name)->second;
    }

    return *(T *)(((char *)this) + offset);
  }

  static MetaData<Class> *GetMeta()
  {
    return MetaRegister<Class>::GetMeta();
  }

private:
  std::map<std::string,void *> virtualMembers;
};

#define MetaName META_ ## __COUNTER__

#define META_DEFINE(Type) \
  MetaRegister<BaseType<Type>::type> MetaName(#Type);\
  void MetaRegister<BaseType<Type>::type>::RegisterMetaData()\

#define ADD_MEMBER(Member) \
  AddMember(#Member,(unsigned)&NullCast()->Member);
