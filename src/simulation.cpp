#include "simulation.hpp"
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <sstream>
#include "global.hpp"
#include "font.hpp"
#include "food.hpp"
#include "image.hpp"
#include "input.hpp"
#include "maze.hpp"
#include "mixer.hpp"
#include "wipe.hpp"
#include "dijkstra.hpp"
#include "permutation.hpp"
using namespace std;
extern Point Steiner[6];
vector<vector<Point>> all_paths;
map<string,vector<Point>> all_mutual_paths;
int counter = 0;
int h = -1;
vector<Point> k ;
int b = 1000000;

void Simulation::game_title()  {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);

    const Point title_pos = Point{180, 160};
    const Point Mus = Point{215,245};
    const char *title_str = "TSP Simulator";
    switch (game_count_) {
      case 0: {
        wipe_->set_wipe_in();
        wipe_->draw(640);
        game_count_++;
        break;
      }
      case 1: {
        draw_text(0, rgb::black, title_pos, title_str);
        wipe_->draw(640);
        if (wipe_->update()) {
          game_count_++;
        }
        break;
      }
      case 2: {
        draw_text(0, rgb::black, title_pos, title_str);
        if (blink_count_ < 30) {
          draw_text(1, rgb::black, Point{215, 300}, "P r e s s   S p a c e   K e y ");
          blink_count_++;
        } else if (blink_count_ < 60) {
          blink_count_++;
        } else {
          blink_count_=0;
        }

        if (input_manager_->edge_key_p(0, 4)) {
          game_count_++;
          blink_count_ = 0;
        }
        break;
      }
      case 3: {
        draw_text(0, rgb::black, title_pos, title_str);
        if (!input_manager_->press_key_p(0, 4)) {
          game_count_++;
        }
        break;
      }
      case 4: {
        draw_text(0, rgb::black, title_pos, title_str);
        game_count_++;
        break;
      }
      case 5: {

        wipe_->draw(640);
        if (wipe_->update()) {
          maze_->init();
          make_permute();
          //cout <<"ALL Permute Size = "<<all_paths.size()<<endl;
          food_->init(*maze_);

          game_count_ = 0;
          game_state_ = game_state::start;
          game_level_ = 1;

          srand((unsigned int)time(nullptr));
        }
        break;
      }
      default:
        break;
    }
}

void Simulation::game_start()  {
    maze_->draw();
    food_->draw();
    draw_score(to_string(k.size()),to_string(b));
    const SDL_Rect src = {0, 0, 20, 20};
    SDL_Texture *p_texture = nullptr;
    p_texture = image_manager_->get(14);
    SDL_Texture *q_texture = nullptr;
    q_texture = image_manager_->get(6);
    SDL_Texture *r_texture = nullptr;
    r_texture = image_manager_->get(15);    
    int x = game_count_;
    cout<<game_count_<<endl;
    for (auto p: Steiner){
        cout<<p.x<<" "<<p.y<<endl;
    }
    //cout<<"completed"<<endl;
    if (game_count_ == 0){
        k = all_paths[counter];
        b = (k.size() < b) ? k.size(): b;
        if (b == k.size()){h = counter;}
        counter +=1;
        if (counter == all_paths.size()){counter = 0;}
    }
    for (int i = 0;i<all_paths[h].size();i++){
        SDL_Rect dst;
        dst.x = (20 * all_paths[h][i].x);
        dst.y = (20 * all_paths[h][i].y);  
        SDL_QueryTexture(r_texture, nullptr, nullptr, &dst.w, &dst.h);
        image_manager_->render_copy(*r_texture, src, dst);      
    }
    //cout<<"out of get path"<<endl;
    //cout<<" K Size = "<<k.size()<<endl;
    for (int i = 0;i<game_count_;i++){
        //cout<<"Inside"<<endl;
        SDL_Rect dst;
        dst.x = (20 * k[i].x);
        dst.y = (20 * k[i].y);
        if (i == game_count_ -1){
            SDL_QueryTexture(q_texture, nullptr, nullptr, &dst.w, &dst.h);
            image_manager_->render_copy(*q_texture, src, dst);
        }else{
            SDL_QueryTexture(p_texture, nullptr, nullptr, &dst.w, &dst.h);
            image_manager_->render_copy(*p_texture, src, dst);
        }
        //SDL_Delay(25);
    }
    SDL_DestroyTexture(p_texture);
    SDL_DestroyTexture(q_texture);
    SDL_DestroyTexture(r_texture);
    game_count_++;
    cout <<"Reached1"<<endl;
    game_count_ = game_count_%(k.size());
    cout <<"Reached2"<<endl;
}