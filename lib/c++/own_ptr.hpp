/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <c++/config.hpp>

namespace system
{
    template <typename ClassType>
    class own_ptr final
    {
    public:
        explicit own_ptr() : m_pClass(nullptr) { }

        ~own_ptr() noexcept { this->release(); }

        COPY_DELETE(own_ptr);

        ClassType* operator->() const { return this->get(); }
        ClassType* get() const { return m_pClass; }

        template <typename ...Args>
        void borrow(Args... args) noexcept
        {
            if (!m_pClass)
                m_pClass = new ClassType(static_cast<Args&&>(args)...);
        }

        void release() noexcept
        {
            if (m_pClass)
                delete m_pClass;

            m_pClass = nullptr;
        }

    private:
        ClassType* m_pClass;

    };
}
