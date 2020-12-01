// ============================================================================
// 类名：HashSet
// 说明：单词模糊查询，推荐正确单词
// 备注：
// 修订：徐景周(jingzhou_xu@163.com)
// 组织：未来工作室(Future Studio)
// 日期：2005.12.1
// =============================================================================
#include  "hashset.h"

using namespace std;


// we do not compute prime numbers but use a table instead
static const int num_primes = 25;
static const unsigned long prime_list[] = {
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
    196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
    50331653, 100663319, 201326611, 402653189, 805306457
};

template<class key_type, class hash_func, class key_equal>
bool HashSet<key_type,hash_func,key_equal>::search(const key_type& k) {

    int p = hf(k) % table_size();

    while ((*ht)[p].used) {
        if (eq((*ht)[p].key, k)) {       // equality predicate for key_type
            return true;
        }
        p++;
        if (p == table_size()) {
            p = 0;  // wrap around to beginning
        }
    }

    return false;
}

template<class key_type, class hash_func, class key_equal>
void HashSet<key_type,hash_func,key_equal>::remove(const key_type& k) {

    int p = hf(k) % table_size();

    while ((*ht)[p].used) {
        if (eq((*ht)[p].key, k)) { 
            (*ht)[p].used = false;
			entries--;
			break;
        }
        p++;
        if (p == table_size()) {
            p = 0;  // wrap around to beginning
        }
    }
    
}


template<class key_type, class hash_func, class key_equal>
void HashSet<key_type,hash_func,key_equal>::insert(const key_type& k) {

    if (load_factor() > .7) {
        resize();
    }

    int pp = hf(k) % table_size();
    int p = pp;

    while (p < table_size() && (*ht)[p].used) {
        p++;
    }
    
    if (p == table_size()) {
        p = 0;
    }
    
    while ((*ht)[p].used) {
        p++;
    }

    (*ht)[p].key = k;
    (*ht)[p].used = true;
    entries++;

}

template<class key_type, class hash_func, class key_equal>
int HashSet<key_type,hash_func,key_equal>::resize() {

    if (prime == num_primes - 1) {
        cerr << "maximal table size reached, aborting ... " << endl;
        exit(2);
    }

    int mm = prime_list[prime];
    prime++;
    int m = prime_list[prime];
    vector<Entry>* ptr = new vector<Entry>(m);

    for (int i = 0; i < mm; ++i) {
    
        if ((*ht)[i].used) {
            key_type kk = (*ht)[i].key;

            int p = hf(kk) % m;

            while (p < m && (*ptr)[p].used) {
                p++;
            }
            if (p == m) {
                p = 0;
            }
            while ((*ptr)[p].used) {
                p++;
            }

            (*ptr)[p].key = kk;
            (*ptr)[p].used = true;
        }
    }

    delete ht;
    ht = ptr;
    return  m;
}
