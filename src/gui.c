#include "init.h"

const float mouse_size = 20;

float* move_mod_x = 0;
float* move_mod_y = 0;

Graph** graphs = 0;
int num_graphs = 0;

void demo_parabola()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_parabola());
  graphs[0]->num_roots = bezier_analytic_roots(graphs[0]->bezier, &graphs[0]->roots);
}

void demo_parabola_subrange()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(bezier_subrange(sample_bezier_parabola(), 0.3f, 0.7f));
  graphs[0]->num_roots = bezier_analytic_roots(graphs[0]->bezier, &graphs[0]->roots);
}

void demo_parabola_split()
{
  Bezier* b = sample_bezier_parabola();
  Bezier* left = 0;
  Bezier* right = 0;

  bezier_split(b, 0.5f, &left, &right);
  
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(left);
  graphs[1] = graph_create(right);

  graphs[0]->num_roots = bezier_analytic_roots(graphs[0]->bezier, &graphs[0]->roots);
  graphs[1]->num_roots = bezier_analytic_roots(graphs[1]->bezier, &graphs[1]->roots);
}

void demo_parabola_two_subranges()
{
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(bezier_subrange(sample_bezier_parabola(), 0.3f, 0.4f));
  graphs[1] = graph_create(bezier_subrange(sample_bezier_parabola(), 0.5f, 0.7f));
  
  graphs[0]->num_roots = bezier_analytic_roots(graphs[0]->bezier, &graphs[0]->roots);
  graphs[1]->num_roots = bezier_analytic_roots(graphs[1]->bezier, &graphs[1]->roots);
}

void demo_sinus()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_sinus(10, 3.1415f));
}

void demo_cosinus()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_cosinus(10, 3.1415f));
}

void demo_sinus_reduction(int n, int freq)
{
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  float** reduction_matrix = bezier_reduction_matrix(n, 2);
  graphs[0] = graph_create(
    bezier_degree_reduction(sample_bezier_sinus(n, freq), 2, reduction_matrix));
  graphs[1] = graph_create(sample_bezier_sinus(n, freq));
  graphs[1]->color_r = 0.0f;
  graphs[1]->color_g = 0.0f;
  graphs[1]->color_b = 1.0f;
}

void demo_cosinus_reduction(int n, int freq)
{
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  float** reduction_matrix = bezier_reduction_matrix(n, 2);
  graphs[0] = graph_create(
    bezier_degree_reduction(sample_bezier_cosinus(10, freq), 2, reduction_matrix));
  graphs[1] = graph_create(sample_bezier_cosinus(n, freq));
  graphs[1]->color_r = 0.0f;
  graphs[1]->color_g = 0.0f;
  graphs[1]->color_b = 1.0f;
}

void demo_bounds()
{
  const int deg = 10;
  Bezier* original = sample_bezier_cosinus(deg, 7.0f);
  float** reduction_matrix = bezier_reduction_matrix(deg, 2);
  Bezier* reduced_and_raised = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(original, reduced_and_raised);
  Bezier* reduced_up = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_down, -difference);

  num_graphs = 4;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;

  graphs[2] = graph_create(reduced_up);
  graphs[2]->color_r = 0.5f;
  graphs[2]->color_g = 1.0f;
  graphs[2]->color_b = 0.5f;

  graphs[3] = graph_create(reduced_down);
  graphs[3]->color_r = 0.5f;
  graphs[3]->color_g = 1.0f;
  graphs[3]->color_b = 0.5f;
}

void demo_bounds_with_intervals1()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->c[0] = 0.2;
  original->c[1] = 0.1;
  original->c[2] = 0.1;
  original->c[3] = -0.1;
  float** reduction_matrix = bezier_reduction_matrix(deg, 2);
  Bezier* reduced_and_raised = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(original, reduced_and_raised);
  Bezier* reduced_up = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_down, -difference);

  num_graphs = 4;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;

  graphs[2] = graph_create(reduced_up);
  graphs[2]->color_r = 0.5f;
  graphs[2]->color_g = 1.0f;
  graphs[2]->color_b = 0.5f;

  graphs[3] = graph_create(reduced_down);
  graphs[3]->color_r = 0.5f;
  graphs[3]->color_g = 1.0f;
  graphs[3]->color_b = 0.5f;

  graphs[0]->num_intervals = bezier_intervals_between(reduced_up, reduced_down, &graphs[0]->intervals);
}

void demo_bounds_with_intervals2()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->c[0] = -0.2;
  original->c[1] = 0.1;
  original->c[2] = 0.1;
  original->c[3] = -0.1;
  float** reduction_matrix = bezier_reduction_matrix(deg, 2);
  Bezier* reduced_and_raised = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(original, reduced_and_raised);
  Bezier* reduced_up = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_down, -difference);

  num_graphs = 4;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;

  graphs[2] = graph_create(reduced_up);
  graphs[2]->color_r = 0.5f;
  graphs[2]->color_g = 1.0f;
  graphs[2]->color_b = 0.5f;

  graphs[3] = graph_create(reduced_down);
  graphs[3]->color_r = 0.5f;
  graphs[3]->color_g = 1.0f;
  graphs[3]->color_b = 0.5f;

  graphs[0]->num_intervals = bezier_intervals_between(reduced_up, reduced_down, &graphs[0]->intervals);
}


void demo_bounds_with_intervals3()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->c[0] = 0.2;
  original->c[1] = -0.1;
  original->c[2] = -0.1;
  original->c[3] = 0.1;
  float** reduction_matrix = bezier_reduction_matrix(deg, 2);
  Bezier* reduced_and_raised = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(original, reduced_and_raised);
  Bezier* reduced_up = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_down, -difference);

  num_graphs = 4;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;

  graphs[2] = graph_create(reduced_up);
  graphs[2]->color_r = 0.5f;
  graphs[2]->color_g = 1.0f;
  graphs[2]->color_b = 0.5f;

  graphs[3] = graph_create(reduced_down);
  graphs[3]->color_r = 0.5f;
  graphs[3]->color_g = 1.0f;
  graphs[3]->color_b = 0.5f;

  graphs[0]->num_intervals = bezier_intervals_between(reduced_up, reduced_down, &graphs[0]->intervals);
}


void demo_bounds_with_intervals4()
{
  const int deg = 3;
  Bezier* original = bezier_create(deg);
  original->dom->a = 0.4;
  original->dom->b = 0.6;
  original->c[0] = 0.2;
  original->c[1] = 0.1;
  original->c[2] = -0.1;
  original->c[3] = 0.2;
  float** reduction_matrix = bezier_reduction_matrix(deg, 2);
  Bezier* reduced_and_raised = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(original, reduced_and_raised);
  Bezier* reduced_up = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_inc_coeffs(reduced_down, -difference);

  num_graphs = 4;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;

  graphs[2] = graph_create(reduced_up);
  graphs[2]->color_r = 0.5f;
  graphs[2]->color_g = 1.0f;
  graphs[2]->color_b = 0.5f;

  graphs[3] = graph_create(reduced_down);
  graphs[3]->color_r = 0.5f;
  graphs[3]->color_g = 1.0f;
  graphs[3]->color_b = 0.5f;

  graphs[0]->num_intervals = bezier_intervals_between(reduced_up, reduced_down, &graphs[0]->intervals);
}

void demo_reduced_and_raised()
{
  const int deg = 10;
  Bezier* original = sample_bezier_cosinus(deg, 7.0f);
  float** reduction_matrix = bezier_reduction_matrix(deg, 2);
  Bezier* reduced_and_raised = bezier_degree_reduction(original, 2, reduction_matrix);
  bezier_degree_raise(reduced_and_raised, deg);

  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(original);
  graphs[1] = graph_create(reduced_and_raised);
  graphs[1]->color_r = 0.5f;
  graphs[1]->color_g = 0.5f;
  graphs[1]->color_b = 0.5f;
}

void demo_intervals1()
{
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(sample_bezier_parabola());

  assert(0);
  //graphs[0]->num_intervals = bezier_above(graphs[0]->bezier, &graphs[0]->intervals);
}

void demo_intervals2()
{
  Bezier* b = sample_bezier_parabola();
  bezier_inc_coeffs(b, -0.35f);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  assert(0);
  //graphs[0]->num_intervals = bezier_above(b, &graphs[0]->intervals);
}

void demo_intervals3()
{
  Bezier* b = sample_bezier_parabola();
  b->c[2] = -0.1f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  assert(0);
  //graphs[0]->num_intervals = bezier_above(b, &graphs[0]->intervals);
}

void demo_intervals4()
{
  Bezier* b = sample_bezier_parabola();
  bezier_inc_coeffs(b, 0.4f);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  assert(0);
  //graphs[0]->num_intervals = bezier_quad_above(b, &graphs[0]->intervals);
}

void demo_intervals5()
{
  Bezier* b = sample_bezier_parabola();
  bezier_inc_coeffs(b, -0.5f);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  assert(0);
  //graphs[0]->num_intervals = bezier_quad_above(b, &graphs[0]->intervals);
}

void demo_intervals6()
{
  Bezier* b = bezier_create(2);
  b->c[0] = -0.2;
  b->c[1] = 0.4;
  b->c[2] = -0.2;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  assert(0);
  //graphs[0]->num_intervals = bezier_quad_above(b, &graphs[0]->intervals);
}

void demo_intervals7()
{
  Bezier* b = bezier_create(2);
  b->c[0] = 0.2;
  b->c[1] = 0.4;
  b->c[2] = -0.2;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  assert(0);
  //graphs[0]->num_intervals = bezier_quad_above(b, &graphs[0]->intervals);
}

void demo_quadclip1()
{
  Bezier* b = sample_bezier_sinus(7, 30);
  b->c[0] = 0.1;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_roots(b, &graphs[0]->roots, 0.001f, 3);
}

void demo_quadclip2()
{
  Bezier* b = sample_bezier_cosinus(7, 30);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_roots(b, &graphs[0]->roots, 0.001f, 3);
}

void demo_cubic_roots1()
{
  Bezier* b = sample_bezier_cosinus(3, 30);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_cubic_roots2()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.5;
  b->c[1] = -1.0f;
  b->c[2] = 1.0;
  b->c[3] = -0.5;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_cubic_roots3()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.5;
  b->c[1] = 0.4f;
  b->c[2] = -0.4f;
  b->c[3] = -0.5;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}


void demo_cubic_roots4()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.5;
  b->c[1] = 0.4f;
  b->c[2] = -0.4f;
  b->c[3] = 0.5;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_above1()
{
  Bezier* b = bezier_create(2);
  b->c[0] = 0.5;
  b->c[1] = 0.6f;
  b->c[2] = -0.6f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
}

void demo_above2()
{
  Bezier* b = bezier_create(2);
  b->c[0] = -0.5;
  b->c[1] = 0.6f;
  b->c[2] = -0.6f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_above3()
{
  Bezier* b = bezier_create(3);
  b->c[0] = -0.5;
  b->c[1] = 0.6f;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_above4()
{
  Bezier* b = bezier_create(3);
  b->c[0] = -0.5;
  b->c[1] = 0.8f;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_between()
{
  Bezier* b = bezier_create(3);
  b->c[0] = -0.5;
  b->c[1] = 0.8f;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  Bezier* b2 = bezier_copy(b);
  bezier_inc_coeffs(b2, 0.1);
  graphs[1] = graph_create(b2);

  graphs[0]->num_intervals = bezier_intervals_between( b2, b, &graphs[0]->intervals);
}

void init()
{
  //demo_parabola();
  //demo_parabola_subrange();
  //demo_parabola_two_subranges();
  //demo_parabola_split();
  //demo_sinus();
  //demo_cosinus();

  //demo_sinus_reduction(10, 3.1415f);
  //demo_cosinus_reduction(10, 3.1415f);
  //demo_sinus_reduction(30, 3.1415f);
  //demo_cosinus_reduction(30, 3.1415f);
  
  //demo_sinus_reduction(10, 50.0f);
  //demo_cosinus_reduction(10, 50.0f);
  //demo_sinus_reduction(30, 50.0f);
  //demo_cosinus_reduction(30, 50.0f);

  //demo_reduced_and_raised();
  //demo_bounds();

  //demo_intervals1();
  //demo_intervals2();
  //demo_intervals3();
  //demo_intervals4();
  //demo_intervals5();
  //demo_intervals6();
  //demo_intervals7();

  //demo_bounds_with_intervals1();
  //demo_bounds_with_intervals2();
  //demo_bounds_with_intervals3();
  demo_bounds_with_intervals4();

  //demo_quadclip1();
  //demo_quadclip2();

  //demo_cubic_roots1();
  //demo_cubic_roots2();
  //demo_cubic_roots3();
  //demo_cubic_roots4();

  //demo_above1();
  //demo_above2();
  //demo_above3();
  //demo_above4();

  //demo_between();
}

void update()
{
}

void draw()
{
  for(int g = 0; g < num_graphs; ++g)
    graph_draw(graphs[g]);

  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  
  // mouse
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_STRIP);
  for(float i = 0; i < 2 * 3.1415; i += 0.1)
    glVertex2f(mouse_size * cosf(i) + getMouseX(), mouse_size * sinf(i) + getMouseY());
  glEnd();
}

void key_press(unsigned char key) {}
void mouse_move() {}
void mouse_left_click() {}
void mouse_right_click() {}
