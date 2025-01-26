
template <typename T>
class rbtree {
public:

	struct rbtree_node : {
		typedef rbtree_node this_type;
		this_type* node_right_;
		this_type* node_left_;
		this_type* node_parent_;
		char mColor;
    	T value_;
	};

	using node = rbtree_node;
	using reference = T&;
    using const_reference =const T&;

	struct rbtree_iterator {
    public:
    	rbtree_iterator() noexcept;
    	rbtree_iterator(node* node) noexcept;
    	reference operator*() const;
		rbtree_iterator& operator++();
		rbtree_iterator  operator++(int);
		rbtree_iterator& operator--();
		rbtree_iterator  operator--(int);
		bool operator==(const rbtree_iterator& lhs);
		bool operator!=(const rbtree_iterator& lhs);
	private:
		friend class rbtree;
		node* current_;
	};
	
	rbtree() noexcept;
	rbtree(rbtree_node* node);
	rbtree(const rbtree& other) noexcept;
	rbtree(rbtree&& other) noexcept;
	~rbtree();

	rbtree& operator=(const rbtree& other) noexcept;
	rbtree& operator=(rbtree&& other) noexcept;

	void rotate_left(node* pos);
	void rotate_right(node* pos);
	void insert(const T& value);
	void remove(const T& value);
	void fix_insertion(node* pos);
	void fix_removing(node* pos);
	
};

template <typename T>
inline rbtree<T>::rbtree_iterator::rbtree_iterator() noexcept : current_(nullptr) {}

template <typename T>
inline rbtree<T>::rbtree_iterator::rbtree_iterator(node* node) noexcept : current_(node) {}

template <typename T>
inline rbtree<T>::reference rbtree<T>::rbtree_iterator::operator*() const {
  return current_->value;
}

template <typename T>
inline rbtree<T>::rbtree_iterator& rbtree<T>::rbtree_iterator::operator++() {
  if(current_ != nullptr) {
	if(current_->node_right_) {
		current_ = current_->node_right_;
		while (current_->node_left_) {
			current_ = current_->node_left_;
		}
	} else {
		node* temp = current_->node_parent_;
		while(current_ == temp->node_right_) {
			current_ = temp;
			temp = current_->node_parent_;
		}
		if(current_->node_right_ != temp) {
			current_ = temp;
		}
	}	
  }
  return *this;
}

template <typename T>
inline rbtree<T>::rbtree_iterator rbtree<T>::rbtree_iterator::operator++(int)
{
	rbtree_iterator temp(current_);
	++(*this);
	return temp;
}

template <typename T>
inline rbtree<T>::rbtree_iterator &rbtree<T>::rbtree_iterator::operator--()
{
	if(current_ != nullptr){
		if(current_->node_left_) {
		current_ = current_->node_left_;
		while (current_->node_right_) {
			current_ = current_->node_right_;
		}
		} else {
			node* temp = current_->node_parent_;
			while(current_ == temp->node_left_) {
				current_ = temp;
				temp = current_->node_parent_;
			}
			current_ = temp;
		}
	}
	return *this;
}

template <typename T>
inline rbtree<T>::rbtree_iterator rbtree<T>::rbtree_iterator::operator--(int)
{
	rbtree_iterator temp(current_);
	--(*this);
	return temp;
}

template <typename T>
inline bool rbtree<T>::rbtree_iterator::operator==(const rbtree_iterator &lhs)
{
   return this->current_ == lhs.current_;
}

template <typename T>
inline bool rbtree<T>::rbtree_iterator::operator!=(const rbtree_iterator &lhs)
{
    return this->current_ != lhs.current_;
}
