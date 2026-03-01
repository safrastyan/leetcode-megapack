class Solution {
public:
    
    int box_index(int i, int j)
    {
        return (i / 3) * 3 + j / 3;
    }
    
    void initialize(const std::vector<std::vector<char>>& board)
    {
        rows = cols = boxes = std::vector<std::vector<int>>(9, std::vector<int>(10, 0));
        
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == '.') {
                    coords.push_back(std::make_pair(i, j));
                    continue;
                }
                int n = board[i][j] - '0';
                rows[i][n] = cols[j][n] = boxes[box_index(i, j)][n] = 1;
            }
        }
    }
    
    void assign(std::pair<int, int> p, int n)
    {
        int r = p.first;
        int c = p.second;
        rows[r][n] = cols[c][n] = boxes[box_index(r, c)][n] = 1;
    }
    
    bool can_assign(std::pair<int, int> p, int n)
    {
        int r = p.first;
        int c = p.second;
        return rows[r][n] == 0 && cols[c][n] == 0 && boxes[box_index(r, c)][n] == 0;
    }
    
    void unassign(std::pair<int, int> p, int n)
    {
        int r = p.first;
        int c = p.second;
        rows[r][n] = cols[c][n] = boxes[box_index(r, c)][n] = 0;
    }
    
    bool rec(std::vector<std::vector<char>>& board, int index)
    {
        if (index == coords.size()) {
            return true;
        }
            
        for (int i = 1; i <= 9; ++i) {
            if (can_assign(coords[index], i)) {
                assign(coords[index], i);
                board[coords[index].first][coords[index].second] = '0' + i;
                if (rec(board, index + 1)) {
                    return true;
                }
                unassign(coords[index], i);
                board[coords[index].first][coords[index].second] = '.';
            }
        }       
        return false;
    }
    
    
    void solveSudoku(vector<vector<char>>& board) 
    {
        initialize(board);
        rec(board, 0);
    }
    
    std::vector<std::vector<int>> rows;
    std::vector<std::vector<int>> cols;
    std::vector<std::vector<int>> boxes;
    std::vector<std::pair<int, int>> coords;
    
    
    
};