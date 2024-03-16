//
// Created by 18746 on 2024/3/9.
//

#ifndef IPV4_MELIALIB_H
#define IPV4_MELIALIB_H



//
// Created by 18746 on 2024/3/9.
//
#include "include.h"
#include "mytbf.h"
#include <glob.h>
#include <cstring>
#include <fstream>
#include <mutex>
using namespace std;
class channel_context{
public:
    chnid_t _chnid;
    string _desc;
    string _path;
    vector<string> _music_path;
    int _pos;
//    mytbf * tbf;
    int offset;
    ifstream file;

};

class medialib {
private:
    std::string _path;
    mutex _mutex;

public:
    std::vector<channel_context*> _channel_list;
public:
    medialib(){
        _path = DIR;
        listMusicFiles();
    }

    medialib( string path) : _path(path) {
        listMusicFiles();
    }

    int mlib_readchn(int chnid, char * buf, int size) {
        unique_lock<mutex> lock(_mutex);
        std::streamsize len = 0;
        memset(buf, 0, sizeof(buf));
        channel_context * ch = _channel_list[chnid];
//        int token = ch->tbf->mytbf_fetch_token(size);
        int token = 10;
        while (true) {
            ch->file.read(buf, token);
            len = ch->file.gcount();

            if (len <= 0) {
                open_next(chnid);
                if (!ch->file.is_open()) {
                    return -1; // Error: Cannot open next file
                }
            } else {
                break;
            }
        }

//        if (len < token) {
//            ch->tbf->mytbf_return_token(token - len);
//        }

        return len;
    }

    void open_next(int chnid) {
        channel_context * ch = _channel_list[chnid];
        ch->_pos = (ch->_pos + 1) % ch->_music_path.size();
        ch->offset = 0;
        ch->file.close();
        ch->file.open(ch->_music_path[ch->_pos], std::ios::binary);

    }

    void listMusicFiles() {
//        mytbf_mang & tbfmand = mytbf_mang::get_instance();
        const std::string& path = _path;
        std::string pattern = path + "/*";
        glob_t globResult;
        glob_t globResult2;
        glob_t globResult3;
        int ch_id = 0;
        if(glob(pattern.c_str(), GLOB_TILDE, NULL, &globResult) == 0){
            for(int i = 0; i < globResult.gl_pathc; i++) {
                channel_context* channel = new channel_context;
                channel->_chnid = ch_id++;
                channel->_pos = 0;
                channel->offset = 0;
//                channel->tbf = tbfmand.get_tbf(MP3_BITRATE / 8, MP3_BITRATE / 8 * 5);
                channel->_path = globResult.gl_pathv[i];
                std::string pattern2 = channel->_path + "/*.mp3";
                if(glob(pattern2.c_str(), GLOB_TILDE, NULL, &globResult2) == 0){
                    for(int j = 0; j < globResult2.gl_pathc; j++){
                        channel->_music_path.push_back(globResult2.gl_pathv[j]);
                    }
                }

                string pattern3 = channel->_path + "/*.txt";
                if(glob(pattern3.c_str(), GLOB_TILDE, NULL, &globResult3) == 0){
                    ifstream file(globResult3.gl_pathv[0]);
                    string line;
                    if(file.is_open()){
                        while(getline(file, line)){
                            channel->_desc += line;
                        }
                        file.close();
                    }
                }

                channel->file.open(channel->_music_path[0], ios::binary);

                if(!channel->file.is_open()){
                    delete channel;
                    ch_id--;
                    continue;
                }
                _channel_list.push_back(channel);
            }
        }
        globfree(&globResult);
        globfree(&globResult2);
        globfree(&globResult3);
    }
    ~medialib() {
        for(size_t i = 0; i < _channel_list.size(); i++) {
            delete _channel_list[i];
        }
    }

};


#endif //IPV4_MELIALIB_H
