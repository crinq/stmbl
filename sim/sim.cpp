#include "sim.h"


int main(){
  float sim_time = 0.0;
  float sim_step = 0.0001;
  float sim_end_time = 2;

  srand(14235);

  // e240
  mot_c mot;
  mot.reset();
  mot.mech_spec.max_rps = 83.3;
  mot.mech_spec.mot_type = mot_c::mech_spec_s::DC;
  mot.mech_spec.pole_count = 1;
  mot.mech_spec.friction = 0.021;//0.021;
  mot.mech_spec.damping = 0.0000426;//0.0000426;
  mot.mech_spec.inertia = 0.0000268;//0.0000268;

  mot.elec_spec.max_i = 13.9;
  mot.elec_spec.i = 1.9;
  mot.elec_spec.nm_a = 0.135;
  mot.elec_spec.r = 5.4;
  mot.elec_spec.l = 0.0082;
  mot.elec_spec.v_rps = 0.852;
  mot.elec_spec.slip = 0;

  mot.feedback.type = mot_c::feedback_s::RES;
  mot.feedback.count = 1;
  mot.feedback.res_offset = 0.0;
  mot.noise.sin_scale = 1.0;
  mot.noise.cos_scale = 1.0;
  mot.noise.sin_offset = 0.0;
  mot.noise.cos_offset = 0.0;
  mot.noise.var = 0.0;

  mot.load.friction = 0.0;
  mot.load.load = 0.0;
  mot.load.damping = 0.0;
  mot.load.inertia = 0.0;

  // bautz e728
  mot_c mot2;
  mot2.reset();
  mot2.mech_spec.max_rps = 50;
  mot2.mech_spec.mot_type = mot_c::mech_spec_s::DC;
  mot2.mech_spec.pole_count = 1;
  mot2.mech_spec.friction = 0.18;
  mot2.mech_spec.damping = 0.004236;
  mot2.mech_spec.inertia = 0.0012;

  mot2.elec_spec.max_i = 60;
  mot2.elec_spec.i = 10;
  mot2.elec_spec.nm_a = 0.36;
  mot2.elec_spec.r = 0.67;
  mot2.elec_spec.l = 0.0011;
  mot2.elec_spec.v_rps = 2.28;
  mot2.elec_spec.slip = 0;

  mot2.feedback.type = mot_c::feedback_s::RES;
  mot2.feedback.count = 1;
  mot2.feedback.res_offset = 0.0;
  mot2.noise.sin_scale = 1.0;
  mot2.noise.cos_scale = 1.0;
  mot2.noise.sin_offset = 0.0;
  mot2.noise.cos_offset = 0.0;
  mot2.noise.var = 0.0;

  mot2.load.friction = 0.0;
  mot2.load.load = 0.0;
  mot2.load.damping = 0.0;
  mot2.load.inertia = 0.0;

  // bosch
  mot_c mot3;
  mot3.reset();
  mot3.mech_spec.max_rps = 16.6;
  mot3.mech_spec.mot_type = mot_c::mech_spec_s::DC;
  mot3.mech_spec.pole_count = 4;
  mot3.mech_spec.friction = 0.065;//0.0;
  mot3.mech_spec.damping = 0.0000826;//0.0;
  mot3.mech_spec.inertia = 0.000141;

  mot3.elec_spec.max_i = 4;
  mot3.elec_spec.i = 2.2;
  mot3.elec_spec.nm_a = 0.2727;
  mot3.elec_spec.r = 15.2;
  mot3.elec_spec.l = 0.0082;//0.030;
  mot3.elec_spec.v_rps = 3.4;//5;
  mot3.elec_spec.slip = 0;

  mot3.feedback.type = mot_c::feedback_s::RES;
  mot3.feedback.count = 1;
  mot3.feedback.res_offset = 0.0;
  mot3.noise.sin_scale = 1.0;
  mot3.noise.cos_scale = 1.0;
  mot3.noise.sin_offset = 0.0;
  mot3.noise.cos_offset = 0.0;
  mot3.noise.var = 0.01;

  mot3.load.friction = 0.0;
  mot3.load.load = 0.0;
  mot3.load.damping = 0.0;
  mot3.load.inertia = 0.0;

  cmd_c cmd;
  cmd.reset();
  cmd.periode = 2;
  cmd.amplitude = 1;
  cmd.wave = cmd_c::SQUARE;
  cmd.type = cmd_c::POS;
  cmd.pos_res = 0.01;
  cmd.vel_res = 0.01;
  cmd.acc_res = 0.01;

  drive_c drive;
  drive.dc = 50;
  drive.pwm_scale = 0.9;
  drive.pwm_res = 8400;
  drive.pid_periode = 0.001;
  drive.mot = &mot3;
  drive.in = &cmd;
  drive.input_cmd = input_cmd;
  drive.input_feedback = input_feedback_real;
  drive.pid = pid;
  drive.output = output;
  drive.reset();

  cout << flush << "time error cur vel ctr" << endl;

  int count = 0;
  int pid_count = drive.pid_periode / sim_step;

  double vel0 = MIN(drive.dc * (2 * drive.pwm_scale - 1) / drive.mot->elec_spec.v_rps, drive.mot->mech_spec.max_rps) * 0.7;
  double ind0 = vel0 * drive.mot->elec_spec.v_rps;
  double volt0 = drive.dc * (2 * drive.pwm_scale - 1);
  double cur0 = (volt0 - ind0) / drive.mot->elec_spec.r;
  double torq0 = cur0 * drive.mot->elec_spec.nm_a;
  double acc0 = torq0 / drive.mot->mech_spec.inertia;

  double vel1 = MIN(drive.dc * (2 * drive.pwm_scale - 1) / drive.mot->elec_spec.v_rps, drive.mot->mech_spec.max_rps) * 0.3;
  double ind1 = vel1 * drive.mot->elec_spec.v_rps;
  double volt1 = drive.dc * (2 * drive.pwm_scale - 1);
  double cur1 = (volt1 - ind1) / drive.mot->elec_spec.r;
  double torq1 = cur1 * drive.mot->elec_spec.nm_a;
  double acc1 = torq1 / drive.mot->mech_spec.inertia;

  double a, b, y;

  a = (acc1 - acc0) / (vel1 - vel0);
  b = acc0 - a * vel0;

  for(sim_time = 0.0; sim_time < sim_end_time; sim_time += sim_step){
    drive.in->step(sim_step);
    if(count == 0){
      drive.step(sim_step * pid_count);
    }
    count++;
    count %= pid_count;
    //drive.state.ctr = 1;
    drive.output(&drive, sim_step);
    drive.mot->step(sim_step);


    //e_pos = (torq - drive.est.load) / drive.est.inertia * exp(-sim_time * mot.elec_spec.v_rps / drive.est.inertia * mot.elec_spec.nm_a / mot.elec_spec.r);
    //y = a * drive.mot->state.vel + b;

    //cout << sim_time << ", " << drive.in->get_pos() << ", " << drive.mot->state.pos << ", " << drive.est.pos << ", " << drive.est.sin_avg << ", " << drive.est.sin_scale << ", " << drive.est.cos_avg << ", " << drive.est.cos_scale << endl;
    //cout << sim_time << ", " << drive.mot->state.pos << ", " << drive.mot->state.vel << ", " << drive.mot->state.acc << ", " << drive.est.p << ", " << drive.est.v << ", " << drive.est.a << endl;//", " << drive.state.ctr << ", " << minus_(drive.in->get_pos(), drive.est.pos) << endl;
    //cout << sim_time << ", " << "-15, " << drive.in->get_pos() * 5 - 15<< ", " << drive.state.ctr * 10 << ", " << drive.mot->state.cur << ", " << drive.mot->state.vel / 5 << ", " << drive.mot->state.pos * 5 - 15 << ", " << minus_(drive.in->state.pos, drive.mot->state.pos) * (-100) - 15 << endl;//", " << drive.state.ctr << ", " << minus_(drive.in->get_pos(), drive.est.pos) << endl;
    cout << sim_time/*drive.mot->state.vel*/ << ", " << minus_(drive.in->state.pos, drive.mot->state.pos) << ", " << drive.mot->state.cur << endl;
  }

  system("gnuplot --persist gp");

  return(0);
}
