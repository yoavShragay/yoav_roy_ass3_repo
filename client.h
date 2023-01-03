#ifndef YOAV_ROY_ASS3_REPO_CLIENT_H
#define YOAV_ROY_ASS3_REPO_CLIENT_H

#include <string>

using namespace std;

bool check_valid_part_ip(char *partIp);

bool check_valid_ip(char *ip);

bool check_valid_port(char *port);

void sendVector(string ip, int port);

#endif //YOAV_ROY_ASS3_REPO_CLIENT_H
