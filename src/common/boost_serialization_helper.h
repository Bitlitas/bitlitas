// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/portable_binary_oarchive.hpp>
#include <boost/archive/portable_binary_iarchive.hpp>
#include <boost/filesystem/operations.hpp>


namespace tools
{
  template<class t_object>
  bool serialize_obj_to_file(t_object& obj, const std::string& file_path)
  {
    TRY_ENTRY();
#if defined(_MSC_VER)
    // Need to know HANDLE of file to call FlushFileBuffers
    HANDLE data_file_handle = ::CreateFile(file_path.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == data_file_handle)
      return false;

    int data_file_descriptor = _open_osfhandle((intptr_t)data_file_handle, 0);
    if (-1 == data_file_descriptor)
    {
      ::CloseHandle(data_file_handle);
      return false;
    }

    const std::unique_ptr<FILE, tools::close_file> data_file_file{_fdopen(data_file_descriptor, "wb")};
    if (nullptr == data_file_file)
    {
      // Call CloseHandle is not necessary
      _close(data_file_descriptor);
      return false;
    }

    // HACK: undocumented constructor, this code may not compile
    std::ofstream data_file(data_file_file.get());
    if (data_file.fail())
    {
      // Call CloseHandle and _close are not necessary
      return false;
    }
#else
    std::ofstream data_file;
    data_file.open(file_path , std::ios_base::binary | std::ios_base::out| std::ios::trunc);
    if (data_file.fail())
      return false;
#endif

    boost::archive::portable_binary_oarchive a(data_file);
    a << obj;
    if (data_file.fail())
      return false;

    data_file.flush();
#if defined(_MSC_VER)
    // To make sure the file is fully stored on disk
    ::FlushFileBuffers(data_file_handle);
#endif

    return true;
    CATCH_ENTRY_L0("serialize_obj_to_file", false);
  }

  template<class t_object>
  bool unserialize_obj_from_file(t_object& obj, const std::string& file_path)
  {
    TRY_ENTRY();

    std::ifstream data_file;  
    data_file.open( file_path, std::ios_base::binary | std::ios_base::in);
    if(data_file.fail())
      return false;
    try
    {
      // first try reading in portable mode
      boost::archive::portable_binary_iarchive a(data_file);
      a >> obj;
    }
    catch(...)
    {
      // if failed, try reading in unportable mode
      boost::filesystem::copy_file(file_path, file_path + ".unportable", boost::filesystem::copy_option::overwrite_if_exists);
      data_file.close();
      data_file.open( file_path, std::ios_base::binary | std::ios_base::in);
      if(data_file.fail())
        return false;
      boost::archive::binary_iarchive a(data_file);
      a >> obj;
    }
    return !data_file.fail();
    CATCH_ENTRY_L0("unserialize_obj_from_file", false);
  }
}
