#include<vector>

template<typename T>
std::vector<T> compress(std::vector<T> &a,bool right=false){
    std::vector<T> res;
    for(auto e:a){
        res.emplace_back(e);
    }
    if(right)for(auto e:a){
        res.emplace_back(e+1);
    }

    std::sort(res.begin() , res.end());
    res.erase(unique(res.begin() , res.end()) , res.end());

    for(auto &e:a){
        e=std::lower_bound(res.begin() , res.end() , e)-res.begin();
    }
    return res;
}

template<typename T>
std::vector<T> compress_2d(std::vector<T> &a,std::vector<T> &b,bool right=false){
    std::vector<T> res;
    for(auto e:a){
        res.emplace_back(e);
    }
    if(right)for(auto e:a){
        res.emplace_back(e+1);
    }
    for(auto e:b){
        res.emplace_back(e);
    }
    if(right)for(auto e:b){
        res.emplace_back(e+1);
    }
    std::sort(res.begin() , res.end());
    res.erase(std::unique(res.begin() , res.end()) , res.end());

    for(auto &e:a){
        e=std::lower_bound(res.begin() , res.end() , e)-res.begin();
    }
    for(auto &e:b){
        e=std::lower_bound(res.begin() , res.end() , e)-res.begin();
    }
    return res;
}