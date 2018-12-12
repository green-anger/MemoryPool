#include <cstdint>


template<typename T>
class MemPool
{
public:
    MemPool();
    ~MemPool();
    void CreatePool( uint32_t num_cells );
    void DestroyPool();
    T* Allocate();
    void Deallocate( void* p );

private:
    uint8_t* AddrFromIndex( uint32_t i ) const;
    uint32_t IndexFromAddr( const uint8_t* p ) const;

    const uint32_t cell_size_;
    uint32_t num_cells_;
    uint32_t num_free_cells_;
    uint32_t num_init_;
    uint8_t* mem_beg_;
    uint8_t* next_;
};


template<typename T>
MemPool<T>::MemPool()
    : cell_size_( sizeof( T ) )
    , num_cells_( 0 )
    , num_free_cells_( 0 )
    , num_init_( 0 )
    , mem_beg_( nullptr )
    , next_( nullptr )
{
    static_assert( sizeof( uint32_t ) <= sizeof( T ), "sizeof( T ) must be equal or greater than sizeof( uint32_t )" );
}


template<typename T>
MemPool<T>::~MemPool()
{
    DestroyPool();
}


template<typename T>
void MemPool<T>::CreatePool( uint32_t num_cells )
{
    num_cells_ = num_cells;
    num_free_cells_ = num_cells_;
    mem_beg_ = new uint8_t[num_cells_ * cell_size_];
    next_ = mem_beg_;
}


template<typename T>
void MemPool<T>::DestroyPool()
{
    delete[] mem_beg_;
    mem_beg_ = nullptr;
}


template<typename T>
T* MemPool<T>::Allocate()
{
    if ( num_init_ < num_cells_ )
    {
        uint32_t* p = reinterpret_cast<uint32_t*>( AddrFromIndex( num_init_ ) );
        *p = ++num_init_;
    }

    T* res = nullptr;

    if ( num_free_cells_ > 0 )
    {
        res = reinterpret_cast<T*>( next_ );

        if ( --num_free_cells_ > 0 )
        {
            next_ = AddrFromIndex( *reinterpret_cast<uint32_t*>( next_ ) );
        }
        else
        {
            next_ = nullptr;
        }
    }

    return res;
}


template<typename T>
void MemPool<T>::Deallocate( void* p )
{
    *static_cast<uint32_t*>( p ) = next_ == nullptr ? num_cells_ : IndexFromAddr( next_ );
    next_ = static_cast<uint8_t*>( p );
    ++num_free_cells_;
}


template<typename T>
uint8_t* MemPool<T>::AddrFromIndex( uint32_t i ) const
{
    return mem_beg_ + ( i * cell_size_ );
}


template<typename T>
uint32_t MemPool<T>::IndexFromAddr( const uint8_t* p ) const
{
    return static_cast<uint32_t>( p - mem_beg_ ) / cell_size_;
}
