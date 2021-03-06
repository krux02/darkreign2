// SMsgUsrPushedUserList.cpp

// DirectoryServer second generation get number of entities message.  Request the
// number of entities for one or more directory paths.  For each path, may request
// number of subdirs, number of services, or total children.


#include "common/won.h"
#include "msg/TMessage.h"
#include "msg/BadMsgException.h"
#include "msg/ServerStatus.h"
#include "../SmallMessageTypesUserSearch.h"
#include "SMsgUsrPushedUserList.h"

// Private namespace for using, types, and constants

namespace 
	{
	using WONMsg::SmallMessage;
	using WONMsg::SMsgUsrPushedUserList;
	using WONMsg::UserUpdateArray;
	using NUserSearchServer::User;
	};

// ** SMsgUsrPushedUserList **

// ** Constructors / Destructor **

// Default ctor

SMsgUsrPushedUserList::SMsgUsrPushedUserList(const unsigned long &i_data_source_id,
										     const unsigned long &i_issue_number,
										     const unsigned char &i_reply_sequence_number,
										     UserUpdateArray *p_output_userarray_for_unpacking,
											 const WONMsg::ServerStatus &server_status,
										     const WONMsg::ServerStatus &data_source_specific_status)
	  			      :SMsgUsrMultipleReplyBase(USER_SEARCH_SERVER_TYPE,
												SMsgUsrPushedUserListTYPE,
												i_reply_sequence_number,
												server_status),
					   m_user_objects_begin(0),
					   m_user_objects_end(0),
					   m_p_output_userarray_for_unpacking(p_output_userarray_for_unpacking),
					   m_i_data_source_id(i_data_source_id),
					   m_i_issue_number(i_issue_number),
					   m_data_source_specific_status(data_source_specific_status)
	{
	}

// SmallMessage ctor

SMsgUsrPushedUserList::SMsgUsrPushedUserList(const SmallMessage& source_message)
				      :SMsgUsrMultipleReplyBase(source_message),
					   m_user_objects_begin(0),
					   m_user_objects_end(0),
					   m_p_output_userarray_for_unpacking(NULL),
					   m_i_data_source_id(0),
					   m_i_issue_number(0),
					   m_data_source_specific_status(WONMsg::StatusCommon_Success)
	{
	}

// Copy ctor

SMsgUsrPushedUserList::SMsgUsrPushedUserList(const SMsgUsrPushedUserList& source_message)
			   :SMsgUsrMultipleReplyBase(source_message),
				m_user_objects_begin(source_message.get_users_begin()),
				m_user_objects_end(source_message.get_users_end()),
				m_p_output_userarray_for_unpacking((const_cast<SMsgUsrPushedUserList *>(&source_message))->get_output_userarray_for_unpacking()),
				m_i_data_source_id(source_message.get_data_source_id()),
				m_i_issue_number(source_message.get_issue_number()),
				m_data_source_specific_status(source_message.get_data_source_specific_status())
	{
	}

// Destructor

SMsgUsrPushedUserList::~SMsgUsrPushedUserList(void)
	{
	}

// ** Public Methods

// Assignment operator

SMsgUsrPushedUserList& SMsgUsrPushedUserList::operator=(SMsgUsrPushedUserList& source_message)
	{
	SMsgUsrMultipleReplyBase::operator=(source_message);

	m_user_objects_begin = source_message.get_users_begin();

	m_user_objects_end = source_message.get_users_end();

	m_p_output_userarray_for_unpacking = source_message.get_output_userarray_for_unpacking();

	m_i_data_source_id = source_message.get_data_source_id();

	m_i_issue_number = source_message.get_issue_number();

	m_data_source_specific_status = source_message.get_data_source_specific_status();

	return *this;
	}

void SMsgUsrPushedUserList::pack_multiple_message_specific_data()
	{
	// Sanity check that the output user array has been set to a non-null value

	if (m_p_output_userarray_for_unpacking)
		{
		// Append the data source id

		AppendLong(m_i_data_source_id);

		// Append the data source specific status information

		AppendShort(static_cast<short>(m_data_source_specific_status));

		// Append the issue number

		AppendLong(m_i_issue_number);

		// Append the number of users found

		AppendLong(get_number_of_users());

		// Cycle through the vector of users, and append each user

		for (unsigned long counter = m_user_objects_begin;
		     counter < m_user_objects_end;
			 counter++)
			{
			// Pack the user data

			((*m_p_output_userarray_for_unpacking)[counter]).m_user.pack_data(*this);

			// Pack the purpose

			AppendLong(((*m_p_output_userarray_for_unpacking)[counter]).m_update_purpose);
			}
		}
	}

void SMsgUsrPushedUserList::unpack_multiple_message_specific_data()
	{
	// Retrieve the data source id

	m_i_data_source_id = ReadLong();

	// Retrieve the data source specific status information

	m_data_source_specific_status = static_cast<WONMsg::ServerStatus>(static_cast<short>(ReadShort()));

	// Retrieve the issue number

	m_i_issue_number = ReadLong();

	// Retrieve the number of users found

	unsigned long number_of_user_objects = ReadLong();

	// Sanity check that the output user array has been set to a non-null value

	if (m_p_output_userarray_for_unpacking)
		{
		// Keep records of the indices of the beginning and end of the users for this message

		m_user_objects_begin = m_p_output_userarray_for_unpacking->size();

		m_user_objects_end = m_user_objects_begin + number_of_user_objects;

		// Retrieve each user, adding each user to the end of the output user array

		for (unsigned long counter = 0;
			 counter < number_of_user_objects;
			 counter++)
			{
			// Add a new user to the end of the array

			m_p_output_userarray_for_unpacking->push_back(UserUpdateObject());

			// Retrieve the user data

			m_p_output_userarray_for_unpacking->back().m_user.unpack_data(*this);

			// Retrieve the purpose

			m_p_output_userarray_for_unpacking->back().m_update_purpose = WONMsg::Purpose(ReadLong());
			}
		}
	}

unsigned long SMsgUsrPushedUserList::get_packed_size_in_bytes() const
	{
	unsigned long result = SMsgUsrMultipleReplyBase::get_packed_size_in_bytes();

	// Add the size of the data source id

	result += sizeof(unsigned long);

	// Add the size of the data source specific status

	result += sizeof(ServerStatus);

	// Add the size of the issue number

	result += sizeof(unsigned long);

	// Add the size of the number users

	result += sizeof(unsigned long);

	// Cycle through the vector of users, and retrieve the packed size of each user

	// Sanity check that the output user array has been set to a non-null value

	if (m_p_output_userarray_for_unpacking)
		{
		for (unsigned long counter = m_user_objects_begin;
		     counter < m_user_objects_end;
			 counter++)
			{
			// Add the size of the user object

			result += ((*m_p_output_userarray_for_unpacking)[counter]).m_user.get_packed_size_in_bytes();

			// Add the size of the purpose object

			result += sizeof(Purpose);
			}
		}

	return result;
	}
