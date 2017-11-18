/* Copyright 2017 Tymoteusz Blazejczyk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "logic_reset_synchronizer.h"

#include <logic/trace.hpp>
#include <logic/gtest/factory.hpp>
#include <gtest/gtest.h>
#include <systemc>

class dut {
public:
    sc_core::sc_clock aclk{"aclk"};
    sc_core::sc_signal<bool> areset_n{"areset_n"};
    sc_core::sc_signal<bool> areset_n_synced{"areset_n_synced"};

    dut() {
        m_dut.aclk(aclk);
        m_dut.areset_n(areset_n);
        m_dut.areset_n_synced(areset_n_synced);
    }
private:
    logic_reset_synchronizer m_dut{"logic_reset_synchronizer"};
    logic::trace<decltype(m_dut)> m_trace{m_dut};
};

static logic::gtest::factory::add<dut> g;

TEST(logic_reset_synchronizer, simple) {
    auto test = logic::gtest::factory::get<dut>();

    test->areset_n = 0;
    sc_start(3, SC_NS);
    test->areset_n = 1;
    sc_start(3, SC_NS);

    EXPECT_TRUE(test->areset_n_synced.read());
}
