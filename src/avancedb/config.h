/*
 *  AvanceDB - an in-memory database similar to Apache CouchDB
 *  Copyright (C) 2015-2017 Ripcord Software
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RS_AVANCEDB_CONFIG_H
#define RS_AVANCEDB_CONFIG_H

#include <string>
#include <cstdint>

#include <boost/program_options.hpp>

class Config final {
public:
    
    Config() = delete;
    Config(const Config&) = delete;
    Config(Config&&) = delete;
    
    static void Parse(int argc, const char** argv);
    
    static const boost::program_options::options_description& Description() noexcept;
    
    static bool IsHelp() noexcept;
    static bool IsDaemon() noexcept;
    
    struct Process final {
        static const std::string& PidFile() noexcept;
        static const std::string& StdOutFile() noexcept;
        static const std::string& StdErrFile() noexcept;
        static const std::string& RootDirectory() noexcept;
        
        static bool Daemonize() noexcept;
        static bool Color() noexcept;
        
    private:
        friend Config;
        
        static std::string pidFile_;
        static std::string stdOutFile_;
        static std::string stdErrFile_;
        static std::string rootDirectory_;
    };
    
    struct Environment final {
        static unsigned CpuCount();
        static unsigned RealCpuCount();
        
    private:
        friend Config;
        
        static unsigned cpuCount_;
    };
    
    struct Http final {
        static const char DefaultAddress[];
        static const unsigned DefaultPort;
        static const unsigned DefaultWorkersPerCpu;
        
        static const std::string& Address() noexcept;
        static unsigned Port() noexcept;
        static unsigned Workers() noexcept;
        static unsigned WorkersPerCpu() noexcept;
        
    private:
        friend Config;
        
        static std::string address_;
        static unsigned port_;
        static unsigned workersPerCpu_;
    };
    
    struct SpiderMonkey final {
        static const std::uint32_t DefaultHeapSizeMB;
        static const std::uint32_t DefaultNurserySizeMB;

        static std::uint32_t HeapSize() noexcept;
        static std::uint32_t NurserySize() noexcept;
        static bool EnableBaselineCompiler() noexcept;
        static bool EnableIonCompiler() noexcept;

    private:
        friend Config;

        static std::uint32_t heapSizeMB_;
        static std::uint32_t nurserySizeMB_;
    };
    
    struct MapReduce final {
        static const float DefaultWorkersPerCpu;

        static unsigned Workers() noexcept;
        static float WorkersPerCpu() noexcept;

    private:
        friend Config;

        static float workersPerCpu_;
    };
    
    struct Data final {
        /// The amount of time, in seconds, to wait after a database has been removed
        /// before the database destructor is called
        static unsigned DatabaseDeleteDelay() noexcept;
    };
    
    static void Clear() { vm_.clear(); }
    static bool IsEmpty() { return vm_.empty(); }
    
private:
    
    static boost::program_options::options_description desc_;
    static boost::program_options::variables_map vm_;

};

#endif /* RS_AVANCEDB_CONFIG_H */

