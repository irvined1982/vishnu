// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UMS_Data/Configuration.cpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Configuration.hpp"
#include <UMS_Data/User.hpp>
#include <UMS_Data/Machine.hpp>
#include <UMS_Data/LocalAccount.hpp>
#include <UMS_Data/AuthSystem.hpp>
#include <UMS_Data/AuthAccount.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "UMS_Data/UMS_DataPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::UMS_Data;

// Default constructor
Configuration::Configuration()
{

    m_listConfUsers.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::UMS_Data::User, -1, true, false >(this, NULL));
    m_listConfMachines.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::UMS_Data::Machine, -1, true, false >(this, NULL));
    m_listConfLocalAccounts.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::UMS_Data::LocalAccount, -1, true, false >(this, NULL));
    m_ListConfAuthSystems.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::UMS_Data::AuthSystem, -1, true, false >(this, NULL));
    m_ListConfAuthAccounts.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::UMS_Data::AuthAccount, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(ConfigurationImpl__ConfigurationImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Configuration::~Configuration()
{
}

/*PROTECTED REGION ID(Configuration.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& Configuration::getFilePath() const
{
    return m_filePath;
}

void Configuration::setFilePath(::ecore::EString const& _filePath)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_filePath = m_filePath;
#endif
    m_filePath = _filePath;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::UMS_Data::UMS_DataPackage::_instance()->getConfiguration__filePath(),
                _old_filePath,
                m_filePath
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::UMS_Data::User >& Configuration::getListConfUsers()
{
    return *m_listConfUsers;
}

::ecorecpp::mapping::EList< ::UMS_Data::Machine >& Configuration::getListConfMachines()
{
    return *m_listConfMachines;
}

::ecorecpp::mapping::EList< ::UMS_Data::LocalAccount >& Configuration::getListConfLocalAccounts()
{
    return *m_listConfLocalAccounts;
}

::ecorecpp::mapping::EList< ::UMS_Data::AuthSystem >& Configuration::getListConfAuthSystems()
{
    return *m_ListConfAuthSystems;
}

::ecorecpp::mapping::EList< ::UMS_Data::AuthAccount >& Configuration::getListConfAuthAccounts()
{
    return *m_ListConfAuthAccounts;
}

