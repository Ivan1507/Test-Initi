#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

namespace my
{
    class client;

    class server final
    {
        private:
		std::vector<std::string> v;
	public:
		void push_back(const std::string& _str)
		{
                    v.push_back(_str);
		}
		void sort()
		{
                    std::sort(v.begin(), v.end());
		}
	void copy_to_client(client&, size_t);
    };

    class client final
    {
        private:
		std::string arr[100];
	public:
		void print() const
		{
                    for(auto&& u:arr)
		    {
                        std::cout << u << '\n';
		    }
		}
        friend void server::copy_to_client(client& cl, size_t left);
	
    };

    void server::copy_to_client(client& cl, size_t left)
    {
	size_t sz = v.size();
        for(size_t i = 0; left < sz; ++i, ++left)
	{
	    cl.arr[i] = v[left];
	}
    }
}

int main()
{
	my::server ser{};
	size_t n{};
	std::cin >> n;
	for(size_t i = 0; i < n; ++i)
	{
            std::string x;
	    std::cin >> x;
	    ser.push_back(std::move(x));
	}
	ser.sort();
        
	my::client cl{};
	size_t requests{};
	std::cin >> requests;
	for(size_t i = 0; i < requests; ++i)
	{
            size_t left_pos{};
	    std::cin >> left_pos;
	    ser.copy_to_client(cl, left_pos);
	    cl.print();
	}

}
