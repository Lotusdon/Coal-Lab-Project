BruteForce algo 
        #include &lt;iostream&gt;
        #include &lt;string&gt;
        using namespace std;
        void bruteForceSearch(string text, string pattern) {
        int n = text.length();
        int m = pattern.length();
        for (int i = 0; i &lt;= n - m; i++) {
        int j = 0;
        while (j &lt; m &amp;&amp; text[i + j] == pattern[j]) {
        
        j++;
        }
        if (j == m) { // Match found
        cout &lt;&lt; &quot;Pattern found at index &quot; &lt;&lt; i &lt;&lt; endl;
        }
        }
        }

rabikarp alggo 
          #define d 256
          
          void rabinkarp(string text, string pattern, int q)
          {
              int n = text.length();
              int m = pattern.length();
          
              if(m == 0 || m > n)
              {
                  cout << "no valid pattern to search.\n";
                  return;
              }
          
              int p = 0;
              int t = 0;
              int h = 1;
          
              for(int i = 0; i < m - 1; i++)
                  h = (h * d) % q;
          
              for(int i = 0; i < m; i++)
              {
                  p = (d * p + pattern[i]) % q;
                  t = (d * t + text[i]) % q;
              }
          
              cout << "matches at indices: [";
          
              bool first = true;
              bool collided = false;
          
              for(int i = 0; i <= n - m; i++)
              {
                  if(p == t)
                  {
                      bool ok = true;
          
                      for(int j = 0; j < m; j++)
                      {
                          if(text[i + j] != pattern[j])
                          {
                              ok = false;
                              break;
                          }
                      }
          
                      if(ok)
                      {
                          if(!first) cout << ", ";
                          cout << i;
                          first = false;
                      }
                      else
                      {
                          cout << "\nfalse-positive hash collision at index " << i;
                          collided = true;
                      }
                  }
          
                  if(i < n - m)
                  {
                      t = (d * (t - text[i] * h) + text[i + m]) % q;
                      if(t < 0) t += q;
                  }
              }
          
              cout << "]" << endl;
          
              if(!collided)
                  cout << "no hash collisions occurred.\n";
          }

boymore algo 
          #define NO_OF_CHARS 256
          
          void badCharHeuristic(string pattern, int badChar[]) {
              int m = pattern.length();
              for (int i = 0; i < NO_OF_CHARS; i++)
                  badChar[i] = -1;
              for (int i = 0; i < m; i++)
                  badChar[(int)pattern[i]] = i;
          }
          
          void goodSuffixHeuristic(string pattern, int goodSuffix[]) {
              int m = pattern.length();
              int border[m + 1];
          
              for (int i = 0; i <= m; i++) {
                  goodSuffix[i] = 0;
                  border[i] = 0;
              }
          
              int i = m, j = m + 1;
              border[i] = j;
          
              while (i > 0) {
                  while (j <= m && pattern[i - 1] != pattern[j - 1]) {
                      if (goodSuffix[j] == 0)
                          goodSuffix[j] = j - i;
                      j = border[j];
                  }
                  i--;
                  j--;
                  border[i] = j;
              }
          
              j = border[0];
              for (i = 0; i <= m; i++) {
                  if (goodSuffix[i] == 0)
                      goodSuffix[i] = j;
                  if (i == j)
                      j = border[j];
              }
          }
          
          void boyerMooreSearch(string text, string pattern) {
              int n = text.length();
              int m = pattern.length();
          
              int badChar[NO_OF_CHARS];
              int goodSuffix[m + 1];
          
              badCharHeuristic(pattern, badChar);
              goodSuffixHeuristic(pattern, goodSuffix);
          
              bool first = true;
              cout << "Output: [";
          
              int s = 0;
              while (s <= n - m) {
                  int j = m - 1;
          
                  while (j >= 0 && pattern[j] == text[s + j])
                      j--;
          
                  if (j < 0) {
                      if (!first) cout << ", ";
                      cout << s;
                      first = false;
                      s += goodSuffix[0];
                  } else {
                      int badShift = max(1, j - badChar[text[s + j]]);
                      int goodShift = goodSuffix[j + 1];
                      s += max(badShift, goodShift);
                  }
              }
          
              cout << "]" << endl;
          }


kmp alggo 
            void computeLPS(string pattern, int lps[]) {
                int m = pattern.length();
                lps[0] = 0;
                int len = 0;
                int i = 1;
            
                while (i < m) {
                    if (pattern[i] == pattern[len]) {
                        len++;
                        lps[i] = len;
                        i++;
                    } else {
                        if (len != 0)
                            len = lps[len - 1];
                        else {
                            lps[i] = 0;
                            i++;
                        }
                    }
                }
            }
            
            void KMPSearch(string text, string pattern) {
                int n = text.length();
                int m = pattern.length();
                int lps[m];
                computeLPS(pattern, lps);
            
                cout << "LPS Array: [";
                for (int i = 0; i < m; i++) {
                    cout << lps[i];
                    if (i != m - 1) cout << ", ";
                }
                cout << "]" << endl;
            
                cout << "Matches at indices: [";
                bool first = true;
                int i = 0, j = 0;
            
                while (i < n) {
                    if (pattern[j] == text[i]) {
                        i++;
                        j++;
                    }
            
                    if (j == m) {
                        if (!first) cout << ", ";
                        cout << (i - j);
                        first = false;
                        j = lps[j - 1];
                    } else if (i < n && pattern[j] != text[i]) {
                        if (j != 0)
                            j = lps[j - 1];
                        else
                            i++;
                    }
                }
                cout << "]" << endl;
            }

MAXHEAP algo

        class MaxHeap {
        private:
            int* arr;
            int capacity;
            int heapsize;
        
            int parent(int i) { 
                return (i - 1) / 2; 
            }
        
            int left(int i) { 
                return (2 * i) + 1; 
            }
        
            int right(int i) { 
                return (2 * i) + 2; 
            }
        
        public:
        
            MaxHeap(int c) {
                capacity = c;
                arr = new int[c];
                heapsize = 0;
            }
        
            ~MaxHeap() {
                delete[] arr;
            }
        
            void heapifydown(int i) {
                int largest = i;
        
                int l = left(i);
                int r = right(i);
        
                if (l < heapsize && arr[l] > arr[largest])
                    largest = l;
        
                if (r < heapsize && arr[r] > arr[largest])
                    largest = r;
        
                if (largest != i) {
                    int temp = arr[i];
                    arr[i] = arr[largest];
                    arr[largest] = temp;
        
                    heapifydown(largest);
                }
            }
        
            void heapifyup(int i) {
                while (i != 0 && arr[parent(i)] < arr[i]) {
        
                    int temp = arr[i];
                    arr[i] = arr[parent(i)];
                    arr[parent(i)] = temp;
        
                    i = parent(i);
                }
            }
        
            bool isempty() const { 
                return heapsize == 0; 
            }
        
            bool isfull() const { 
                return heapsize == capacity; 
            }
        
            void insert_key(int key) {
                if (isfull()) {
                    cout << "heap overflow" << endl;
                    return;
                }
        
                int i = heapsize;
        
                arr[i] = key;
                heapsize++;
        
                heapifyup(i);
            }
        
            void print() {
                for (int i = 0; i < heapsize; i++) {
                    cout << arr[i] << " ";
                }
                cout << endl;
            }
        
            void delete_at(int i) {
                if (i < 0 || i >= heapsize) {
                    cout << "invalid index" << endl;
                    return;
                }
        
                arr[i] = arr[heapsize - 1];
                heapsize--;
        
                heapifydown(i);
                heapifyup(i);
            }
        
            void update_key(int i, int newval) {
                if (i < 0 || i >= heapsize) {
                    cout << "invalid index" << endl;
                    return;
                }
        
                arr[i] = newval;
        
                heapifydown(i);
                heapifyup(i);
            }
        };

AVL algo 
                struct Node {
                    int data;
                    Node* left;
                    Node* right;
                    int height;  
                
                    Node(int val) {
                        data = val;
                        left = right = NULL;
                        height = 1;
                    }
                };
                
                class AVL {
                    Node* root;
                
                    
                    int get_height(Node* node) {
                        if (node == NULL)
                            return 0;
                        return node->height;
                    }
                
                    int get_balance(Node* node) {
                        if (node == NULL)
                            return 0;
                        return get_height(node->left) - get_height(node->right);
                    }
                
                    void update_height(Node* node) {
                    	int l_h = get_height(node->left);
                    	int r_h = get_height(node->right);
                    	
                        node->height = 1 + max(l_h, r_h);
                    }
                
                    // Right Rotation
                    Node* rotate_right(Node* y) {
                        Node* x = y->left;
                        Node* T2 = x->right;
                
                        x->right = y;
                        y->left = T2;
                
                        update_height(y);
                        update_height(x);
                
                        return x;
                    }
                
                    // Left Rotation
                    Node* rotate_left(Node* x) {
                        Node* y = x->right;
                        Node* T2 = y->left;
                
                        y->left = x;
                        x->right = T2;
                
                        update_height(x);
                        update_height(y);
                
                        return y;
                    }
                    
                    Node* balance_node(Node* node) {
                    int balance = get_balance(node);
                
                    // Left Left Case
                    if (balance > 1 && get_balance(node->left) >= 0)
                        return rotate_right(node);
                
                    // Left Right Case
                    if (balance > 1 && get_balance(node->left) < 0) {
                        node->left = rotate_left(node->left);
                        return rotate_right(node);
                    }
                
                    // Right Right Case
                    if (balance < -1 && get_balance(node->right) <= 0)
                        return rotate_left(node);
                
                    // Right Left Case
                    if (balance < -1 && get_balance(node->right) > 0) {
                        node->right = rotate_right(node->right);
                        return rotate_left(node);
                    }
                
                    // Already balanced
                    return node;
                }
                
                
                    // Insert with AVL balancing
                    Node* insert(Node* node, int val) {
                        if (node == NULL)
                            return new Node(val);
                
                        if (val < node->data)
                            node->left = insert(node->left, val);
                        else if (val > node->data)
                            node->right = insert(node->right, val);
                        else
                            return node; // Duplicates not allowed
                
                        update_height(node);
                        return balance_node(node);
                    }
                
                    // Find node with minimum value
                    Node* find_min(Node* node) {
                        while (node && node->left != NULL)
                            node = node->left;
                        return node;
                    }
                
                    // Delete node with AVL balancing
                    Node* delete_node(Node* node, int val) {
                        if (node == NULL)
                            return node;
                
                        if (val < node->data)
                            node->left = delete_node(node->left, val);
                        else if (val > node->data)
                            node->right = delete_node(node->right, val);
                        else {
                            if (node->left == NULL || node->right == NULL) {
                                Node* temp = node->left ? node->left : node->right;
                
                                if (temp == NULL) {
                                    temp = node;
                                    node = NULL;
                                } else
                                    *node = *temp;
                
                                delete temp;
                            } else {
                                Node* temp = find_min(node->right);
                                node->data = temp->data;
                                node->right = delete_node(node->right, temp->data);
                            }
                        }
                
                        if (node == NULL)
                            return node;
                            
                        update_height(node);
                        return balance_node(node);
                    }
                
                    // Inorder traversal
                    void inorder(Node* node) {
                        if (node != NULL) {
                            inorder(node->left);
                            cout << node->data << " ";
                            inorder(node->right);
                        }
                    }
                
                public:
                    BST() {
                        root = NULL;
                    }
                
                    void insert(int val) {
                        root = insert(root, val);
                    }
                
                    void remove(int val) {
                        root = delete_node(root, val);
                    }
                
                    void display() {
                        inorder(root);
                        cout << endl;
                    }
                };

BST algo 
            struct Node {
            	int data;
            	Node* left;
            	Node* right;
            	Node(int val){
            		data  = val;
            		left = right = NULL;
            	}
            };
            class BST {
            	int count =0;
            	Node* root;
            	Node* insert(Node* node, int val){
            		if(node == NULL){
            			return new Node(val);
            		}
            		if( val < node->data){
            			node->left = insert(node->left, val);
            		}
            		else if(val > node->data){
            			node->right = insert(node->right, val);
            		}
            		return node;
            	}
            	public:
            	BST(){
            		root = NULL;
            	}
            	void insert(int val){
            		root = insert(root, val);
            	}
            	void inorder(Node* node) const{
            		if(node!=NULL){
            			inorder(node->left);
            			cout<<node->data<<" ";
            			inorder(node->right);
            		}
            	}
            	Node* delete_node(Node* node, int val){
            		if(node == NULL){
            			return node;
            		} if(val < node->data){
            			node->left = delete_node(node->left, val);
            		} else if(val > node->data){
            			node->right = delete_node(node->right, val);
            		} else {
            			if(node->left == NULL && node->right == NULL){
            				delete node;
            				return NULL;
            			} else if(node->left == NULL){
            				Node* temp = node->right;
            				delete node;
            				return temp;
            			} else if (node->right == NULL){
            				Node* temp = node->left;
            				delete node;
            				return temp;
            			} else {
            				Node* temp = find_min(node->right);
            				node->data = temp->data;
            				node->right = delete_node(node->right, temp->data);
            			}
            		}
            		return node;
            	}
            	Node* find_min(Node* node){
            		while (node && node->left != NULL)
                        node = node->left;
                    return node;
            	}
            	void remove(int val){
            		root = delete_node(root, val);
            	}
            	void display(){
            		inorder(root);
            	}
            	
            };

Mergesort algo 

          void merge(int a[], int beg, int mid, int end)    
          {    
              int i, j, k;  
              int n1 = mid - beg + 1;    
              int n2 = end - mid;    
                
              int LeftArray[n1], RightArray[n2]; //temporary arrays  
                
              /* copy data to temp arrays */  
              for (int i = 0; i < n1; i++)    
              LeftArray[i] = a[beg + i];    
              for (int j = 0; j < n2; j++)    
              RightArray[j] = a[mid + 1 + j];    
                
              i = 0; /* initial index of first sub-array */  
              j = 0; /* initial index of second sub-array */   
              k = beg;  /* initial index of merged sub-array */  
                
              while (i < n1 && j < n2)    
              {    
                  if(LeftArray[i] <= RightArray[j])    
                  {    
                      a[k] = LeftArray[i];    
                      i++;    
                  }    
                  else    
                  {    
                      a[k] = RightArray[j];    
                      j++;    
                  }    
                  k++;    
              }    
              while (i<n1)    
              {    
                  a[k] = LeftArray[i];    
                  i++;    
                  k++;    
              }    
                
              while (j<n2)    
              {    
                  a[k] = RightArray[j];    
                  j++;    
                  k++;    
              }    
          }    
            
          void mergeSort(int a[], int beg, int end)  
          {  
              if (beg < end)   
              {  
                  int mid = (beg + end) / 2;  
                  mergeSort(a, beg, mid);  
                  mergeSort(a, mid + 1, end);  
                  merge(a, beg, mid, end);  
              }  
          }  

quicksort algo 

          int partition(int a[], int start, int end)  
          {  
              int pivot = a[end]; // Pivot is the last element
              int i = start - 1;  // Index of the smaller element
          
              for(int j = start; j < end; j++) {  
                  if (a[j] <= pivot) {  
                      i++;  
                      // Swap a[i] and a[j]
                      int t = a[i];  
                      a[i] = a[j];  
                      a[j] = t;  
                  }  
              }  
              // Swap a[i + 1] with pivot (a[end])
              int t = a[i + 1];  
              a[i + 1] = a[end];  
              a[end] = t;  
          
              return i + 1;  // Return the partition index
          }
          
            
          /* function to implement quick sort */  
          void quick(int a[], int start, int end) /* a[] = array to be sorted, start = Starting index, end = Ending index */  
          {  
              if (start < end)  
              {  
                  int p = partition(a, start, end); //p is the partitioning index  
                  quick(a, start, p - 1);  
                  quick(a, p + 1, end);  
              }  
          } 

radixsort algo 

          int getMax(int a[], int n) {  
             int max = a[0];  
             for(int i = 1; i<n; i++) {  
                if(a[i] > max)  
                   max = a[i];  
             }  
             return max; //maximum element from the array  
          }  
            
          void countingSort(int a[], int n, int place) // function to implement counting sort  
          {  
            int output[n + 1];  
            int count[10] = {0};    
            
            // Calculate count of elements  
            for (int i = 0; i < n; i++)  
              count[(a[i] / place) % 10]++;  
                
            // Calculate cumulative frequency  
            for (int i = 1; i < 10; i++)  
              count[i] += count[i - 1];  
            
            // Place the elements in sorted order  
            for (int i = n - 1; i >= 0; i--) {  
              output[count[(a[i] / place) % 10] - 1] = a[i];  
              count[(a[i] / place) % 10]--;  
            }  
            
            for (int i = 0; i < n; i++)  
              a[i] = output[i];  
          }  
            
          // function to implement radix sort  
          void radixsort(int a[], int n) {  
             
            // get maximum element from array  
            int max = getMax(a, n);  
            
            // Apply counting sort to sort elements based on place value  
            for (int place = 1; max / place > 0; place *= 10)  
              countingSort(a, n, place);  
          }  

priorityq algo 

            struct Node {
            int value; // The value of the element
            int priority; // The priority of the element
            Node* next; // Pointer to the next node in the queue
            Node(int val, int pri) : value(val), priority(pri), next(nullptr) {}
            };
            // PriorityQueue class
            class PriorityQueue {
            private:
            Node* front; // The front of the queue
            public:
            // Constructor
            PriorityQueue() : front(nullptr) {}
            // Destructor to free the memory
            ~PriorityQueue() {
            while (front) {
            Node* temp = front;
            front = front-&gt;next;
            delete temp;
            }
            }
            // Insert a new element with a given priority
            void insert(int val, int pri) {
            Node* newNode = new Node(val, pri);
            
            
            // If the queue is empty or the new node has higher priority than the front
            if (!front || pri &gt; front-&gt;priority) {
            newNode-&gt;next = front;
            front = newNode;
            } else {
            // Otherwise, find the correct position based on priority
            Node* current = front;
            while (current-&gt;next &amp;&amp; current-&gt;next-&gt;priority &gt;= pri) {
            current = current-&gt;next;
            }
            newNode-&gt;next = current-&gt;next;
            current-&gt;next = newNode;
            }
            }
            // Remove the element with the highest priority (front of the queue)
            void remove() {
            if (!front) {
            cout &lt;&lt; &quot;Queue is empty!&quot; &lt;&lt; endl;
            return;
            }
            Node* temp = front;
            front = front-&gt;next;
            delete temp;
            }
            // Get the element with the highest priority (front of the queue)
            int peek() {
            if (!front) {
            cout &lt;&lt; &quot;Queue is empty!&quot; &lt;&lt; endl;
            return -1; // Error value
            }
            return front-&gt;value;
            }
            // Print the entire queue (from front to back)
            void printQueue() {
            if (!front) {
            cout &lt;&lt; &quot;Queue is empty!&quot; &lt;&lt; endl;
            return;
            
           
            }
            Node* current = front;
            while (current) {
            cout &lt;&lt; &quot;(&quot; &lt;&lt; current-&gt;value &lt;&lt; &quot;, &quot; &lt;&lt; current-&gt;priority &lt;&lt; &quot;) &quot;;
            current = current-&gt;next;
            }
            cout &lt;&lt; endl;
            }
            };
