#include "os_info.h"

OS_info::OS_info(string osname, string osdistr) {
    name = osname;
    distr = osdistr;
}

OS_info::~OS_info() {}

void OS_info::update(const char* path) {
    // update info
    sysinfo(&sys_info);
    statvfs(path, &vfs_info);
    ram_free = sys_info.freeram;
    ram_total = sys_info.totalram;
    disk_free = vfs_info.f_bavail * vfs_info.f_bsize;
    disk_total = vfs_info.f_blocks * vfs_info.f_bsize;
}

long OS_info::get_info(int arg) {
    switch(arg) {
        case 0 : return ram_free;
        case 1 : return ram_total;
        case 2 : return disk_free;
        case 3 : return disk_total;
    }
}

ostringstream OS_info::return_info(int arg) {
    ostringstream oss;
    if(arg) {
        oss << "OS : " << name << endl;
        oss << "Release : " << distr << endl;
    }
    else {
        oss << "Avail : " << setprecision(2) << fixed << disk_free / GB_TO_B << "GB" << endl;
        oss << "Total : " << disk_total / GB_TO_B << "GB" << endl;
    }
    return oss;
}