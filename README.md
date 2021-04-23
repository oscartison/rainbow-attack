# RainbowAttack_54254_55315_55047

g++ -pthread -o crack -std=c++17 random.hpp sha256.cpp passwd-utils.hpp threadpool.hpp mainChain.cpp hash_chain.cpp 

g++ -pthread -o gen -std=c++17 random.hpp sha256.cpp passwd-utils.hpp threadpool.hpp gen-passwd.cpp hash_chain.cpp 
