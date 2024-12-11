#include <iostream>
#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <chrono>
#include <cmath>
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <filesystem>


//����� ��� ������ � �� ����� � ���������� libevdev
std::map<std::string, int> stringsAndKeyCodesMap{   {"Esc", KEY_ESC},
                                                    {"1", KEY_1},
                                                    {"2", KEY_2},
                                                    {"3", KEY_3},
                                                    {"4", KEY_4},
                                                    {"5", KEY_5},
                                                    {"6", KEY_6},
                                                    {"7", KEY_7},
                                                    {"8", KEY_8},
                                                    {"9", KEY_9},
                                                    {"0", KEY_0},
                                                    {"-", KEY_MINUS},
                                                    {"+", KEY_EQUAL},
                                                    {"Backspace", KEY_BACKSPACE},
                                                    {"Tab", KEY_TAB},
                                                    {"q", KEY_Q},
                                                    {"Q", KEY_Q},
                                                    {"w", KEY_W},
                                                    {"W", KEY_W},
                                                    {"e", KEY_E},
                                                    {"E", KEY_E},
                                                    {"r", KEY_R},
                                                    {"R", KEY_R},
                                                    {"t", KEY_T},
                                                    {"T", KEY_T},
                                                    {"y", KEY_Y},
                                                    {"Y", KEY_Y},
                                                    {"u", KEY_U},
                                                    {"U", KEY_U},
                                                    {"i", KEY_I},
                                                    {"I", KEY_I},
                                                    {"o", KEY_O},
                                                    {"O", KEY_O},
                                                    {"p", KEY_P},
                                                    {"P", KEY_P},
                                                    {"[", KEY_LEFTBRACE},
                                                    {"]", KEY_RIGHTBRACE},
                                                    {"Enter", KEY_ENTER},
                                                    {"Left Ctrl", KEY_LEFTCTRL},
                                                    {"a", KEY_A},
                                                    {"A", KEY_A},
                                                    {"s", KEY_S},
                                                    {"S", KEY_S},
                                                    {"d", KEY_D},
                                                    {"D", KEY_D},
                                                    {"f", KEY_F},
                                                    {"F", KEY_F},
                                                    {"g", KEY_G},
                                                    {"G", KEY_G},
                                                    {"h", KEY_H},
                                                    {"H", KEY_H},
                                                    {"j", KEY_J},
                                                    {"J", KEY_J},
                                                    {"k", KEY_K},
                                                    {"K", KEY_K},
                                                    {"l", KEY_L},
                                                    {"L", KEY_L},
                                                    {";", KEY_SEMICOLON},
                                                    {"'", KEY_APOSTROPHE},
                                                    {"`", KEY_GRAVE},
                                                    {"Left Shift", KEY_LEFTSHIFT},
                                                    {"\\", KEY_BACKSLASH},
                                                    {"z", KEY_Z},
                                                    {"Z", KEY_Z},
                                                    {"x", KEY_X},
                                                    {"X", KEY_X},
                                                    {"c", KEY_C},
                                                    {"C", KEY_C},
                                                    {"v", KEY_V},
                                                    {"V", KEY_V},
                                                    {"b", KEY_B},
                                                    {"B", KEY_B},
                                                    {"n", KEY_N},
                                                    {"N", KEY_N},
                                                    {"m", KEY_M},
                                                    {"M", KEY_M},
                                                    {",", KEY_COMMA},
                                                    {".", KEY_DOT},
                                                    {"/", KEY_SLASH},
                                                    {"Right Shift", KEY_RIGHTSHIFT},
                                                    {"*", KEY_KPASTERISK},
                                                    {"Left Alt", KEY_LEFTALT},
                                                    {"Space", KEY_SPACE},
                                                    {"Caps Lock", KEY_CAPSLOCK},
                                                    {"F1", KEY_F1},
                                                    {"F2", KEY_F2},
                                                    {"F3", KEY_F3},
                                                    {"F4", KEY_F4},
                                                    {"F5", KEY_F5},
                                                    {"F6", KEY_F6},
                                                    {"F7", KEY_F7},
                                                    {"F8", KEY_F8},
                                                    {"F9", KEY_F9},
                                                    {"F10", KEY_F10},
                                                    {"Num Lock", KEY_NUMLOCK},
                                                    {"Scroll Lock", KEY_SCROLLLOCK},
                                                    {"Numpad 7", KEY_KP7},
                                                    {"Numpad 8", KEY_KP8},
                                                    {"Numpad 9", KEY_KP9},
                                                    {"Numpad -", KEY_KPMINUS},
                                                    {"Numpad 4", KEY_KP4},
                                                    {"Numpad 5", KEY_KP5},
                                                    {"Numpad 6", KEY_KP6},
                                                    {"Numpad +", KEY_KPPLUS},
                                                    {"Numpad 1", KEY_KP1},
                                                    {"Numpad 2", KEY_KP2},
                                                    {"Numpad 3", KEY_KP3},
                                                    {"Numpad 0", KEY_KP0},
                                                    {"Numpad .", KEY_KPDOT},
                                                    {"F11", KEY_F11},
                                                    {"F12", KEY_F12},
                                                    {"Numpad Enter", KEY_KPENTER},
                                                    {"Right Ctrl", KEY_RIGHTCTRL},
                                                    {"Numpad /", KEY_KPSLASH},
                                                    {"Print Screen", KEY_SYSRQ},
                                                    {"Right Alt", KEY_RIGHTALT},
                                                    {"Home", KEY_HOME},
                                                    {"Arrow Up", KEY_UP},
                                                    {"Page Up", KEY_PAGEUP},
                                                    {"Arrow Left", KEY_LEFT},
                                                    {"Arrow Right", KEY_RIGHT},
                                                    {"End", KEY_END},
                                                    {"Arrow Down", KEY_DOWN},
                                                    {"Page Down", KEY_PAGEDOWN},
                                                    {"Insert", KEY_INSERT},
                                                    {"Delete", KEY_DELETE},
                                                    {"Pause/Break", KEY_PAUSE},
                                                    {"Left Win", KEY_LEFTMETA},
                                                    {"Left Function Key", KEY_LEFTMETA},
                                                    {"Right Win", KEY_RIGHTMETA},
                                                    {"Right Function Key", KEY_RIGHTMETA},
                                                    {"Compose", KEY_COMPOSE}
                                                };


//����� ��� ������ � �� ����� � ���������� libevdev
std::map<int, std::string> keyCodesAndStringsMap{   {KEY_ESC, "Esc"}, 
                                                    {KEY_1, "1"}, 
                                                    {KEY_2, "2"}, 
                                                    {KEY_3, "3"}, 
                                                    {KEY_4, "4"}, 
                                                    {KEY_5, "5"}, 
                                                    {KEY_6, "6"}, 
                                                    {KEY_7, "7"}, 
                                                    {KEY_8, "8"}, 
                                                    {KEY_9, "9"}, 
                                                    {KEY_0, "0"}, 
                                                    {KEY_MINUS, "-"}, 
                                                    {KEY_EQUAL, "+"}, 
                                                    {KEY_BACKSPACE, "Backspace"}, 
                                                    {KEY_TAB, "Tab"}, 
                                                    {KEY_Q, "q"}, 
                                                    {KEY_Q, "Q"}, 
                                                    {KEY_W, "w"}, 
                                                    {KEY_W, "W"}, 
                                                    {KEY_E, "e"}, 
                                                    {KEY_E, "E"}, 
                                                    {KEY_R, "r"}, 
                                                    {KEY_R, "R"}, 
                                                    {KEY_T, "t"}, 
                                                    {KEY_T, "T"}, 
                                                    {KEY_Y, "y"}, 
                                                    {KEY_Y, "Y"}, 
                                                    {KEY_U, "u"}, 
                                                    {KEY_U, "U"}, 
                                                    {KEY_I, "i"}, 
                                                    {KEY_I, "I"}, 
                                                    {KEY_O, "o"}, 
                                                    {KEY_O, "O"}, 
                                                    {KEY_P, "p"}, 
                                                    {KEY_P, "P"}, 
                                                    {KEY_LEFTBRACE, "["}, 
                                                    {KEY_RIGHTBRACE, "]"}, 
                                                    {KEY_ENTER, "Enter"}, 
                                                    {KEY_LEFTCTRL, "Left Ctrl"}, 
                                                    {KEY_A, "a"}, 
                                                    {KEY_A, "A"}, 
                                                    {KEY_S, "s"}, 
                                                    {KEY_S, "S"}, 
                                                    {KEY_D, "d"}, 
                                                    {KEY_D, "D"}, 
                                                    {KEY_F, "f"}, 
                                                    {KEY_F, "F"}, 
                                                    {KEY_G, "g"}, 
                                                    {KEY_G, "G"}, 
                                                    {KEY_H, "h"}, 
                                                    {KEY_H, "H"}, 
                                                    {KEY_J, "j"}, 
                                                    {KEY_J, "J"}, 
                                                    {KEY_K, "k"}, 
                                                    {KEY_K, "K"}, 
                                                    {KEY_L, "l"}, 
                                                    {KEY_L, "L"}, 
                                                    {KEY_SEMICOLON, ";"}, 
                                                    {KEY_APOSTROPHE, "'"}, 
                                                    {KEY_GRAVE, "`"}, 
                                                    {KEY_LEFTSHIFT, "Left Shift"}, 
                                                    {KEY_BACKSLASH, "\\"}, 
                                                    {KEY_Z, "z"}, 
                                                    {KEY_Z, "Z"}, 
                                                    {KEY_X, "x"}, 
                                                    {KEY_X, "X"}, 
                                                    {KEY_C, "c"}, 
                                                    {KEY_C, "C"}, 
                                                    {KEY_V, "v"}, 
                                                    {KEY_V, "V"}, 
                                                    {KEY_B, "b"}, 
                                                    {KEY_B, "B"}, 
                                                    {KEY_N, "n"}, 
                                                    {KEY_N, "N"}, 
                                                    {KEY_M, "m"}, 
                                                    {KEY_M, "M"}, 
                                                    {KEY_COMMA, ","}, 
                                                    {KEY_DOT, "."}, 
                                                    {KEY_SLASH, "/"}, 
                                                    {KEY_RIGHTSHIFT, "Right Shift"}, 
                                                    {KEY_KPASTERISK, "*"}, 
                                                    {KEY_LEFTALT, "Left Alt"}, 
                                                    {KEY_SPACE, "Space"}, 
                                                    {KEY_CAPSLOCK, "Caps Lock"}, 
                                                    {KEY_F1, "F1"}, 
                                                    {KEY_F2, "F2"}, 
                                                    {KEY_F3, "F3"}, 
                                                    {KEY_F4, "F4"}, 
                                                    {KEY_F5, "F5"}, 
                                                    {KEY_F6, "F6"}, 
                                                    {KEY_F7, "F7"}, 
                                                    {KEY_F8, "F8"}, 
                                                    {KEY_F9, "F9"}, 
                                                    {KEY_F10, "F10"}, 
                                                    {KEY_NUMLOCK, "Num Lock"}, 
                                                    {KEY_SCROLLLOCK, "Scroll Lock"}, 
                                                    {KEY_KP7, "Numpad 7"}, 
                                                    {KEY_KP8, "Numpad 8"}, 
                                                    {KEY_KP9, "Numpad 9"}, 
                                                    {KEY_KPMINUS, "Numpad -"}, 
                                                    {KEY_KP4, "Numpad 4"}, 
                                                    {KEY_KP5, "Numpad 5"}, 
                                                    {KEY_KP6, "Numpad 6"}, 
                                                    {KEY_KPPLUS, "Numpad +"}, 
                                                    {KEY_KP1, "Numpad 1"}, 
                                                    {KEY_KP2, "Numpad 2"}, 
                                                    {KEY_KP3, "Numpad 3"}, 
                                                    {KEY_KP0, "Numpad 0"}, 
                                                    {KEY_KPDOT, "Numpad ."}, 
                                                    {KEY_F11, "F11"}, 
                                                    {KEY_F12, "F12"}, 
                                                    {KEY_KPENTER, "Numpad Enter"}, 
                                                    {KEY_RIGHTCTRL, "Right Ctrl"}, 
                                                    {KEY_KPSLASH, "Numpad /"}, 
                                                    {KEY_SYSRQ, "Print Screen"}, 
                                                    {KEY_RIGHTALT, "Right Alt"}, 
                                                    {KEY_HOME, "Home"}, 
                                                    {KEY_UP, "Arrow Up"}, 
                                                    {KEY_PAGEUP, "Page Up"}, 
                                                    {KEY_LEFT, "Arrow Left"}, 
                                                    {KEY_RIGHT, "Arrow Right"}, 
                                                    {KEY_END, "End"}, 
                                                    {KEY_DOWN, "Arrow Down"}, 
                                                    {KEY_PAGEDOWN, "Page Down"}, 
                                                    {KEY_INSERT, "Insert"}, 
                                                    {KEY_DELETE, "Delete"}, 
                                                    {KEY_PAUSE, "Pause/Break"}, 
                                                    {KEY_LEFTMETA, "Left Win"}, 
                                                    {KEY_LEFTMETA, "Left Function Key"}, 
                                                    {KEY_RIGHTMETA, "Right Win"}, 
                                                    {KEY_RIGHTMETA, "Right Function Key"}, 
                                                    {KEY_COMPOSE, "Compose"}
                                                };

class Key;
class KeyHandler;

class Key
{
public:
    //������ ���� ������
    void keyWasPressed();

    //������ ���� ������
    void keyWasReleased();

    //������� ���������� ���������� �� ������� ������
    bool addSubscribe(KeyHandler* inputKeyHandler);

    //������� �������� ���������� ������������ �� ������� ������
    bool deleteSubscribe(KeyHandler* inputKeyHandler);

    //������� ��������� ���� �������
    void setKeyCode(int inputKeyCode);
    

private:
    std::unordered_map<KeyHandler*, std::list<KeyHandler*>::iterator> _keyHandlerHash;
    std::list<KeyHandler*> _keyHandlerList;
    bool _stateKey = false;
    int _keyCode = 0;
};

class KeyHandler
{
public:
    KeyHandler(std::vector<Key>* inputKeyVector);

    bool addKey(int inputKeyCode);

    bool removeKey(int inputKeyCode);

    void keyWasPressed();

    void keyWasReleased();

    void setDurationMs(int inputDuraitonMs);

    void setActionString(std::string inputActionString);

    void activation();


private:
    int _durationMs = 0;                    //������������ �������� ������� ������ � �������������

    std::string _actionString = "nothing";  //������� ����������� ��� ���������

    int _counterKeyPressed = 0;             //������� ������� ������

    std::chrono::time_point<std::chrono::high_resolution_clock> _startTime; //����� ������� ������ �������

    std::unordered_set<int> _keyCodeSet;    //��������� ������

    std::vector<Key>* _keyVector;           //������ ������
};


//������ ���� ������
void Key::keyWasPressed()
{
    if(!_stateKey)
    {
        for(const auto it : _keyHandlerList)
        {
            it->keyWasPressed();
        }

        //���������� ��� ������ ������
        _stateKey = true;
    }
}


//������ ���� ������
void Key::keyWasReleased()
{
    if(_stateKey)
    {
        for(const auto it : _keyHandlerList)
        {
            it->keyWasReleased();
        }

        //���������� ��� ������ ������
        _stateKey = false;
    }
}


//������� ���������� ���������� �� ������� ������
bool Key::addSubscribe(KeyHandler* inputKeyHandler)
{
    //���� ������ ����������
    std::unordered_map<KeyHandler*, std::list<KeyHandler*>::iterator>::iterator findIterator = _keyHandlerHash.find(inputKeyHandler);

    //���� �� �����, �� ��������� ����������
    if(findIterator == _keyHandlerHash.end())
    {  
        //��������� � ������ KeyHandler
        std::list<KeyHandler*>::iterator insertIterator = _keyHandlerList.insert(_keyHandlerList.end(), inputKeyHandler);

        //��������� � ��� KeyHandler
        _keyHandlerHash.insert({inputKeyHandler, insertIterator});

        //������� �������� ����������
        //���������� true
        return true;
    }
    else
    {
        //����� ��������� ��� ����, ���������� �� ���������
        //���������� false
        return false;
    }
}


//������� �������� ���������� ������������ �� ������� ������
bool Key::deleteSubscribe(KeyHandler* inputKeyHandler)
{
    //���� ������ ����������
    std::unordered_map<KeyHandler*, std::list<KeyHandler*>::iterator>::iterator findIterator = _keyHandlerHash.find(inputKeyHandler);

    //���� �����, �� ������� ����������
    if(findIterator != _keyHandlerHash.end())
    {  
        //�������� �������� ������
        std::list<KeyHandler*>::iterator listIterator = findIterator->second;

        //������� �� ������ ��������
        _keyHandlerList.erase(listIterator);

        //������� �� ���� ��������
        _keyHandlerHash.erase(findIterator);

        //inputKeyHandler

        //������� ������� ����������
        //���������� true
        return true;
    }
    else
    {
        //����� ��������� ���, �������� �� ���������
        //���������� false
        return false;
    }
}

void Key::setKeyCode(int inputKeyCode)
{
    _keyCode = inputKeyCode;
}

KeyHandler::KeyHandler(std::vector<Key>* inputKeyVector)
{
    _keyVector = inputKeyVector;
    _startTime = std::chrono::high_resolution_clock::now();
}

bool KeyHandler::addKey(int inputKeyCode)
{
    //���� ������� � inputKeyCode
    std::map<int, std::string>::iterator findIterator1 = keyCodesAndStringsMap.find(inputKeyCode);

    //���� ����� ������� ���
    if(findIterator1 == keyCodesAndStringsMap.end())
    {
        std::cerr << "\n\nFailed to add key, key not exist." << std::endl;

        //���������� false, ��� ��� �� ������� ����� ����� �������
        return false;
    }


    //������� inputKeyCode ����������
    //����� ���� �� ��� ����� ������� � KeyHandler
    std::unordered_set<int>::iterator findIterator2 = _keyCodeSet.find(inputKeyCode);
    
    //����� ������� ��� ���� � KeyHandler
    if(findIterator2 != _keyCodeSet.end())
    {
        //����� ��� �������
        std::string keyName = findIterator1->second;

        std::cerr << "\n\nFailed to add key, observer already contains such a key. Key: " << keyName << "." << std::endl;

        //���������� false, ��� ��� ����� ������� � KeyHandler ��� ����
        return false;
    }


    //������� inputKeyCode ����������
    //� KeyHandler ��� ������� inputKeyCode
    //�������� ������ �� �������, �� ������� ����� �����������
    Key& refKey = (*_keyVector)[inputKeyCode];

    //��������� ���������� � �������
    if(refKey.addSubscribe(this))
    {
        //��������� ������� �� ���������
        _keyCodeSet.insert(inputKeyCode).second;

        //���������� true, ��� ��� ������ �������� �������
        return true;
    }
    else
    {
        std::cerr << "\n\nFailed to add key." << std::endl;

        //���������� false, ��� ��� �� ������� �������� �������
        return false;
    }
}

bool KeyHandler::removeKey(int inputKeyCode)
{
    //���� ������� � inputKeyCode
    std::map<int, std::string>::iterator findIterator1 = keyCodesAndStringsMap.find(inputKeyCode);

    //���� ����� ������� ���
    if(findIterator1 == keyCodesAndStringsMap.end())
    {
        std::cerr << "\n\nFailed to remove key, key not exist." << std::endl;

        //���������� false, ��� ��� �� ������� ����� ����� �������
        return false;
    }


    //������� inputKeyCode ����������
    //����� ���� �� ��� ����� ������� � KeyHandler
    std::unordered_set<int>::iterator findIterator2 = _keyCodeSet.find(inputKeyCode);
    
    //����� ������� ��� ���� � KeyHandler
    if(findIterator2 != _keyCodeSet.end())
    {
        //����� ��� �������
        std::string keyName = findIterator1->second;

        std::cerr << "\n\nFailed to remove key, observer not contains this key. Key: " << keyName << "." << std::endl;

        //���������� false, ��� ��� ����� ������� � KeyHandler ���
        return false;
    }


    //������� inputKeyCode ����������
    //� KeyHandler ���� ������� inputKeyCode
    //�������� ������ �� �������, �� ������� ����� ����������
    Key& refKey = (*_keyVector)[inputKeyCode];

    //������� ���������� � �������
    if(refKey.deleteSubscribe(this))
    {
        //������� ��� ������� �� ���������
        _keyCodeSet.erase(findIterator2);
    }
    else
    {
        std::cerr << "\n\nFailed to remove key." << std::endl;
    }

    //���������� true, ��� ��� ������ ������� �������
    return true;
}

void KeyHandler::keyWasPressed()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = currentTime - _startTime;

    int currentDuration_ms = round(duration.count()*1000);

    if(currentDuration_ms > _durationMs)
    {
        _counterKeyPressed = 0;
    }
    
    if(_counterKeyPressed == 0)
    {   
        _startTime = std::chrono::high_resolution_clock::now();
    }

    _counterKeyPressed++;

    if(_counterKeyPressed > _keyCodeSet.size())
    {
        _counterKeyPressed == _keyCodeSet.size();
    }

    if(_counterKeyPressed >= _keyCodeSet.size())
    {
        activation();
        _counterKeyPressed = 0;
    }
}

void KeyHandler::keyWasReleased()
{
    _counterKeyPressed--;
    
    if(_counterKeyPressed < 0)
    {
        _counterKeyPressed = 0;
    }
}

void KeyHandler::setDurationMs(int inputDuraitonMs)
{
    _durationMs = inputDuraitonMs;
}

void KeyHandler::setActionString(std::string inputActionString)
{
    _actionString = inputActionString;
}

void KeyHandler::activation()
{
    system(_actionString.c_str());
}


std::string execCommand(const std::string cmd, int& out_exitStatus)
{
    out_exitStatus = 0;

    auto pPipe = ::popen(cmd.c_str(), "r");

    if(pPipe == nullptr)
    {
        throw std::runtime_error("Cannot open pipe");
    }

    std::array<char, 256> buffer;

    std::string result;

    while(not std::feof(pPipe))
    {
        auto bytes = std::fread(buffer.data(), 1, buffer.size(), pPipe);
        result.append(buffer.data(), bytes);
    }

    auto rc = ::pclose(pPipe);

    if(WIFEXITED(rc))
    {
        out_exitStatus = WEXITSTATUS(rc);
    }

    return result;
}

bool deviceExists(const std::string& devicePath) 
{
    return (access(devicePath.c_str(), F_OK) != -1);
}

int main(int argc, char* argv[])
{    
    std::vector<Key> keyVector;
    
    keyVector.resize(KEY_COMPOSE + 1);

    for(int i = 0; i < keyVector.size(); i++)
    {
        keyVector[i].setKeyCode(i);
    }


    std::list<KeyHandler> keyHandlerList;


    // // �������� YAML �����
    // const char* filename = "CaptureKeyUtilityConfig.yaml";

    // //��������� ����
    // FILE* file = fopen(filename, "r");
    // if(!file)
    // {
    //     std::cerr << "Failed to open file " << filename << std::endl;
    //     //��������� ������ ��� ������ �������
    //     std::cerr << "Error: " << strerror(errno) << std::endl;
    //     return 1;
    // }

    // //������ ���������� ����� � ������
    // fseek(file, 0, SEEK_END);
    // long fileSize = ftell(file);
    // fseek(file, 0, SEEK_SET);

    // std::string fileContent(fileSize, '\0');
    // fread(&fileContent[0], 1, fileSize, file);
    // fclose(file);

    // YAML::Node config = YAML::Load(fileContent);


    // �������� ���� � ������������ �����
    std::filesystem::path executablePath = std::filesystem::absolute(argv[0]);

    // �������� ���������� ������������ �����
    std::filesystem::path executableDir = executablePath.parent_path();

    //��������� ����
    YAML::Node config = YAML::LoadFile(std::string(executableDir) + "/" + "CaptureKeyUtilityConfig.yaml");


    //�������� ������� ���� keyboard_shortcuts
    YAML::Node keyboard_shortcutsYAML = config["keyboard_shortcuts"];

    if(keyboard_shortcutsYAML)
    {
        for(const auto& shortcut : keyboard_shortcutsYAML)
        {
            //����� ���������� �� ���� duration
            YAML::Node durationYAML = shortcut["duration"];
            if(!durationYAML)
            {  
                std::cerr << "Not found duration in the YAML file.\n\n";
                continue;
            }

            //��������� ���
            if(durationYAML.Type() != YAML::NodeType::Scalar)
            {
                std::cerr << "Not found duration in the YAML file.\n\n";
                continue;
            }
            
            //�������� �������� �� ���� keyboard_shortcuts
            int duration = durationYAML.as<int>();
            

            //����� ���������� �� ���� action_string
            YAML::Node action_stringYAML = shortcut["action_string"];

            if(!action_stringYAML)
            {  
                std::cerr << "Not found action_string in the YAML file.\n\n";
                continue;
            }

            //��������� ���
            if(action_stringYAML.Type() != YAML::NodeType::Scalar)
            {
                std::cerr << "Not found action_string in the YAML file.\n\n";
                continue;
            }

            //�������� �������� �� ���� action_string
            std::string action_string = action_stringYAML.as<std::string>();


            //����� ���������� �� ���� keys
            YAML::Node keysYAML = shortcut["keys"];

            if(!keysYAML)
            {  
                std::cerr << "Not found keys in the YAML file.\n\n";
                continue;
            }

            //�������� �������� �� ���� keys
            std::vector<std::string> keysStrings;

            //����� �������� �� ���� keys �������������������
            switch(keysYAML.Type())
            {
                case YAML::NodeType::Sequence:
                {
                    //�������� �������� �� ���� keys
                    keysStrings = keysYAML.as<std::vector<std::string>>();
                    break;
                }
                case YAML::NodeType::Scalar:
                {
                    //�������� �������� �� ���� keys
                    std::string keyString = keysYAML.as<std::string>();
                    keysStrings.push_back(keyString);
                    break;
                }
                default:
                    std::cerr << "Not found keys in the YAML file.\n\n";
                    continue;
                    break;
            }


            //��������� �� ������ �� ��� ����
            if(keysStrings.empty())
            {
                std::cerr << "Keys is empty.\n\n";
                continue;
            }


            std::vector<int> keysCodes;
            std::vector<int> indexErrorVector;


            //����� ������
            std::cout << "Duration: " << duration << "\n";
            std::cout << "Action String: " << action_string << "\n";
            std::cout << "Keys: ";
            
            
            //����������� ������ � ����
            for(int i = 0; i < keysStrings.size(); i++)
            {
                //���� ��������������� ������ ���
                std::map<std::string, int>::iterator findIterator = stringsAndKeyCodesMap.find(keysStrings[i]);

                //���� �� �����, �� ��������� � ������ ������ ������ ������
                if(findIterator == stringsAndKeyCodesMap.end())
                {
                    indexErrorVector.push_back(i);
                }
                else
                {
                    //�����, ������� �� �����
                    if(i > 0)
                    {
                        std::cout << ", ";
                    }

                    std::cout << keysStrings[i];

                    //��������� ��� ������� � ������� ����� ������
                    keysCodes.push_back(findIterator->second);
                }
            }
            
            //���� �������� ���� ������� �� ���� ���������
            if(keysCodes.empty())
            {
                std::cerr << "Keys is empty.\n\n";
            }
            else
            {
                keyHandlerList.push_back(KeyHandler(&keyVector));
                KeyHandler& refKeyHandler = keyHandlerList.back();
                refKeyHandler.setDurationMs(duration);
                refKeyHandler.setActionString(action_string);

                for(const auto& key : keysCodes)
                {
                    //��������� �������
                    bool res = refKeyHandler.addKey(key);

                    // //���� �� ����� �������� �������
                    // if(!res)
                    // {
                    //     //������� ����� ����������� �������
                    //     for(const auto& key : keysCodes)
                    //     {
                    //         refKeyHandler.removeKey(key);
                    //     }

                    //     keyHandlerList.pop_back();

                    //     continue;
                    // }
                }
            }

            for(const auto& index : indexErrorVector)
            {
                //���� �� �����, �� ����������
                std::cerr << "\n\nFailed to add key, key not exist, key: " << keysStrings[index] << "\n\n";
            }

            std::cout << "\n\n";
        }
    }
    else
    {
        std::cerr << "Not found keyboard_shortcuts in the YAML file.\n" << std::endl;
    }


    int fd;
    struct libevdev *dev = nullptr;
    int rc;


    while(true)
    {
        std::vector<std::string> deviceVector;

        const std::string inputDir = "/dev/input";

        for(const auto& entry : std::filesystem::directory_iterator(inputDir))
        {
            if(entry.is_character_file())
            {
                std::string filename = entry.path().filename().string();

                if(filename.compare(0, 5, "event") == 0)
                {
                    deviceVector.push_back(entry.path());
                }
            }
        }


        bool deviceFinded = false;
       
        for(const auto& currentDevice : deviceVector)
        {
            fd = open(currentDevice.c_str(), O_RDONLY);

            if(fd < 0)
            {
                std::cerr << "Failed open device, error:" << strerror(-fd) << std::endl;
            }

            rc = libevdev_new_from_fd(fd, &dev);
            if(rc < 0)
            {
                std::cerr << "Failed initialization library libevdev, error: " << strerror(-rc) << std::endl;
                close(fd);
            }


            // ��������� ���� �������
            if(libevdev_has_event_type(dev, EV_ABS))
            {
                close(fd);
                continue;
            }
            if(libevdev_has_event_type(dev, EV_REL))
            {
                close(fd);
                continue;
            }
            if(libevdev_has_event_type(dev, EV_KEY))
            {
                deviceFinded = true;
                break;
            }
        }
        
        if(!deviceFinded)
        {
            sleep(1);
            continue;
        }


        std::cout << "Device: " << libevdev_get_name(dev) << std::endl;
        
        while(true)
        {
            struct input_event ev;

            int rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);

            if(rc == LIBEVDEV_READ_STATUS_SUCCESS)
            {
                if(ev.type == EV_KEY)
                {
                    switch(ev.value)
                    {
                        //������� ���� ������
                        case 0:
                        {
                            keyVector[ev.code].keyWasReleased();
                            break;
                        }
                        //������� ���� ������
                        case 1:
                        {
                            keyVector[ev.code].keyWasPressed();
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            else if(rc == LIBEVDEV_READ_STATUS_SYNC)
            {
                continue;
            }
            else
            {  
                //��������� ������ ��� ������ �������
                std::cerr << "Failed read event, error: " << strerror(-rc) << std::endl;

                if(-rc == 19)
                {
                    close(fd);
                    break;
                }
            }
        }
    }

    libevdev_free(dev);
    close(fd);
    return 0;
}
