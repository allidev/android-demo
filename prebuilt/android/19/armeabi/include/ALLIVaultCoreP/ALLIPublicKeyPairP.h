/*
* Copyright (C) ALLI Enterprises, Inc. ALL rights reserved.
*
* This file is part of ALLIVault. For full terms see the included
* COPYING file.
*/
#pragma once
#include "alli_common.h"

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		/**
		* Class ALLIPublicKeyPairP. It handles all operations related to
		* importing/exporting a public-private key pair.
		*/
		class ALLIPublicKeyPairP
		{
		public:
			/**
			* Class constructor. Create an ALLIPublicKeyPairP object.
			*
			* @param uname username associated with the key pair
			*/
			ALLIVAULTCOREP_API explicit ALLIPublicKeyPairP(const std::string &uname);
			/**
			* Class copy constructor.
			*
			* @param src a const reference to an ALLIPublicKeyPairP object
			*/
			ALLIPublicKeyPairP(const ALLIVaultCore::Helpers::ALLIPublicKeyPairP &src);
			/**
			* Class destructor.
			*/
			ALLIVAULTCOREP_API ~ALLIPublicKeyPairP();
			/**
			 * Import a key-pair from a designated source
			 *
			 * @param keyDir the folder where the key-pair source is located
			 * @return true on success, false otherwise
			 */
			ALLIVAULTCOREP_API bool importKeyPair(const boost::filesystem::path &keyDir);
			/**
			 * Export a key-pair to a designated destination
			 *
			 * @param keyDir the folder where to save the key-pair
			 */
			ALLIVAULTCOREP_API void exportKeyPair(const boost::filesystem::path &keyDir);

		private:
			class ALLIPublicKeyPairP_impl;
			std::unique_ptr<ALLIPublicKeyPairP_impl> pimpl;
		};
	}
}

