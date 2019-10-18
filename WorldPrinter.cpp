#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;
const int WORLD_WIDTH = 201;
const int WORLD_HEIGHT = 55;
const int FULL_LOGITUDE = 180;
const int FULL_LATITUDE = 90;
#define RED     "\033[31m"      /* Red */
#define WHITE   "\033[37m"      /* White */

class World {
    //地图的长度
private:
    int width;
    int high;
    char** arr;
public:
    World(string file) {
        width = WORLD_WIDTH;
        high  = WORLD_HEIGHT;
        char buffer[256];
        ifstream ifile;
        ifile.open(file);
        arr = new char*[high];
        for(int i=0; i<high; i++) {
            arr[i] = new char[width];
            for(int j=0 ;j<width;j++){
                arr[i][j]=' ';
            }
        }
        for(int i=0;i<high;i++) {
            ifile.getline(buffer,256);
            memcpy(arr[i],buffer,width);
        }
    };
    ~World(){
        for(int i=0;i<high;i++){
            delete []arr[i];
        }
        delete []arr;
    }
    void Print() {

        for(int i =0; i<high; i++) {
            for(int j=0;j<width;j++){
                if(arr[i][j] == '@'){
                    cout<<RED;
                }
                cout<<arr[i][j];
                cout<<WHITE;
            }
            cout<<endl;
        }
    };
    //对应x,y轴  东经是正数，西经是负数,北纬是正数，南纬是负数
    void Where(double log, double lat){
        int x = int ((log*width/2)/FULL_LOGITUDE);
        int y = int ((lat*high/2)/FULL_LATITUDE);

        if(x>0){
            x+=width/2;
        }
        y=high/2-y;


        char temp = arr[y][x];
        arr[y][x]='@';
        Print();
    }
};

int main() {

    World world  = World("/Users/kfpa/Desktop/world.txt");
//    world.Print();
    int x,y;
    cout<<"一次输入经度和纬度，东西经用正负表示，北南纬用正负表示"<<endl;

    x = 116;
    y= 40;

    world.Where(x,y);
}
