#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <memory>

const int N = 20;


class WorldGame {
private:
    std::vector<std::pair<double, std::pair<int, int>>> _changes_coord;
    std::vector<std::vector<int>> _grid;
    std::vector<std::pair<double, std::vector<std::vector<int>>>> _states; //вектор<{dt, новое состояние}}>

public:
    WorldGame(std::vector<std::vector<int>>& grid) : _grid(grid) {}

    double random_double_ln() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        return -(log(dis(gen)));
    }

    std::vector<std::vector<int>>& get_grid()  {
        return this->_grid;
    }

    void set_grid(const std::vector<std::vector<int>>& new_grid) {
        this->_grid = new_grid;
    }

    std::vector<std::pair<double, std::pair<int, int>>> get_changes() {
        return this->_changes_coord;
    }

    const std::vector<std::pair<double, std::vector<std::vector<int>>>>& get_state() const {
        return this->_states;
    }

    void add_state(std::pair<double, std::vector<std::vector<int>>> state) {
        this->_states.emplace_back(state);
    }


    void clear_states() {
        this->_states.clear();
    }

    void print_grid() {
        for (const auto& vec : get_grid()) {
            for (const auto& num : vec) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    int num_of_neigthbores(size_t& i, size_t& j) {
        int res = 0;
        if (j > 0 && get_grid()[i][j - 1] == 1)
            res++;
        if (j < (N - 1) && get_grid()[i][j + 1] == 1)
            res++;
        if (i > 0 && get_grid()[i - 1][j] == 1)
            res++;
        if (i < (N - 1) && get_grid()[i + 1][j] == 1)
            res++;
        return res;
    }

    std::unique_ptr<std::pair<double, std::vector<std::vector<int>>>>  get_min_dt_step() {

        for (size_t i = 0; i < get_grid().size(); ++i) {
            for (size_t j = 0; j < get_grid()[i].size(); ++j) {

                if (get_grid()[i][j] == 0) {
                    continue;
                }

                int num_of_neightbore = num_of_neigthbores(i, j);

                if (num_of_neightbore > 3) {
                    std::vector<std::vector<int>> temp = get_grid();
                    temp[i][j] = 0;
                    double dt = random_double_ln() / 2.0;
                    add_state({ dt, temp });
                    //get_changes().push_back(std::make_pair(e, std::make_pair(i, j)));
                }

                if (num_of_neightbore == 0) { // Клетка ходит

                    if (j < (N - 1) && get_grid()[i][j + 1] == 0) { // клетка ходит вправо
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i][j + 1] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (j > 0 && get_grid()[i][j - 1] == 0) { // клетка ходит влево
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i][j - 1] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (i > 0 && get_grid()[i - 1][j] == 0) { // клетка ходит вверх
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i - 1][j] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (i < (N - 1) && get_grid()[i + 1][j] == 0) { // клетка ходит вниз
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i + 1][j] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }
                }

                else if (num_of_neightbore < 3) { // Рождение новой клетки или ход старой
                    

                    if (i > 0 && get_grid()[i - 1][j] == 0) { // клетка рожает вверх
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i - 1][j] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (i < (N - 1) && get_grid()[i + 1][j] == 0) { // клетка рожает вниз
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i + 1][j] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (j < (N - 1) && get_grid()[i][j + 1] == 0) { // клетка рожает вправо
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j + 1] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (j > 0 && get_grid()[i][j - 1] == 0) { // клетка рожает влево
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j - 1] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (j < (N - 1) && get_grid()[i][j + 1] == 0) { // клетка ходит вправо
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i][j + 1] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (j > 0 && get_grid()[i][j - 1] == 0) { // клетка ходит влево
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i][j - 1] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (i > 0 && get_grid()[i - 1][j] == 0) { // клетка ходит вверх
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i - 1][j] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                    if (i < (N - 1) && get_grid()[i + 1][j] == 0) { // клетка ходит вниз
                        std::vector<std::vector<int>> temp = get_grid();
                        temp[i][j] = 0;
                        temp[i + 1][j] = 1;
                        double dt = random_double_ln() / 3.0;
                        add_state({ dt, temp });
                    }

                }
           

                if (num_of_neightbore > 3) { // Клетка умирает
                    std::vector<std::vector<int>> temp = get_grid();
                    temp[i][j] = 0;
                    double dt = random_double_ln() / 2.0;
                    add_state({ dt, temp });
                }
            }
        }

        auto states = get_state();

        if (states.empty()) {
            std::cout << "GAME OVER" << std::endl;
            return nullptr;
        }


        std::sort(states.begin(), states.end(), [](const auto& lhs, const auto& rhs) { // Сортируем по возрастанию dt
            return lhs.first < rhs.first;
            });

        auto result =  std::make_unique<std::pair<double, std::vector<std::vector<int>>>>(states[0]);
        clear_states();
        states.clear();
        
        return result;
    }

    void life() {
        double t = 0;
        int iter = 0;
        while (t <= 10 * N * N) {

            ++iter;
            auto step(get_min_dt_step());

            if (step) {
                set_grid(step->second);
                t += step->first;
                std::cout << "Current Iteration: " << iter << std::endl;
                std::cout << "Current T: " << t << std::endl;
                std::cout << "Current state: " << std::endl;
                print_grid();
                std::cout << "----------------------------------------" << std::endl;
            }

            else {
                break;
            }
                
        }
        
    }
};

int main()
{
    std::vector<std::vector<int>> init_grid(N, std::vector<int>(N, 0));
    init_grid[5][5] = 1;
    init_grid[15][5] = 1;
    init_grid[5][15] = 1;
    init_grid[15][15] = 1;

    std::unique_ptr<WorldGame> world_game_ptr = std::make_unique<WorldGame>(init_grid);
    
    std::cout << "Init grid" << std::endl;
    world_game_ptr->print_grid();
    std::cout << "-------------------" << std::endl;
    world_game_ptr->life();

    return 0;
}
