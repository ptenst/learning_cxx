#include <vector>
#include <iostream>

class Test
{
public:
    Test(){
        std::cout << "default construct\n";
        data_ = new int(0);
    }
    Test(int a){
        std::cout << "construct " << a << " \n";
        data_ = new int(a);
    }
    Test(const Test &rhs){
        std::cout << "copy construct " << *rhs.data_ << " \n";
        data_ = new int();
        *data_ = *rhs.data_;
    }
    Test& operator=(const Test &rhs){
        std::cout << "copy operator " << *rhs.data_ << " \n";
        data_ = new int();
        *data_ = *rhs.data_;
    }
    Test(Test &&rhs){
        std::cout << "move construct " << *rhs.data_ << " \n";
        data_ = rhs.data_;
        rhs.data_ = nullptr;
    }
    Test& operator=(Test &&rhs){
        std::cout << "move operator " << *rhs.data_ << " \n";
        data_ = rhs.data_;
        rhs.data_ = nullptr;
    }
    ~Test(){
        delete data_;
        data_ = nullptr;
    }
    int data(){
        if(data_)
            return *data_;
        else{
            return 0;
        }
    }
private:
    int *data_;
};

int main()
{
    std::vector<Test> new_vec {1};
    new_vec.emplace_back(2);
    auto print_v = [&new_vec](std::vector<Test> &tail_vec){
        std::cout << "the lhs one is: ";
        for(auto &&ele : new_vec){
            std::cout << ele.data() << " ";
        }    
        std::cout << "after append, the rhs one is: ";
        for(auto &&ele : tail_vec){
            std::cout << ele.data() << " ";
        }
        std::cout << std::endl;
    };
    std::vector<Test> copy_vec {3, 4};
    new_vec.insert(new_vec.end(), copy_vec.begin(), copy_vec.end());
    print_v(copy_vec);

    std::vector<Test> move_vec {33, 44};
    new_vec.reserve(7);
    std::cout << "reserve finished\n";
    new_vec.insert(new_vec.end(), std::make_move_iterator(move_vec.begin()), std::make_move_iterator(move_vec.end()));
    print_v(move_vec);
    return 0;
}