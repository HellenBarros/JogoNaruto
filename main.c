#include <allegro.h>
#include <math.h>
#include <time.h>

/// variaveis globais
int colidir(int ax, int ay, int bx, int by, int aw, int ah, int bw, int bh);
int m;
int caindo = 1;
float vel_y = 0;
float gravidade = 0.1;
float eixo_y = 0.0;

volatile int timer;
void incrementa_timer() { timer++; }
END_OF_FUNCTION(incrementa_timer)

volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

volatile int milisegundos;
void msec_counter() { milisegundos++; }
END_OF_FUNCTION(msec_counter)

///função menu
int menu()
{
    BITMAP* buf = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* seta = load_bitmap("seta.bmp", NULL);
    BITMAP* fundo = load_bitmap("fundo.bmp", NULL);
    BITMAP* logo = load_bitmap("logo.bmp", NULL);

    int setay = 260;
    m = 1;



    while(m==1)
    {


            if(key[KEY_S])
            {
                setay = 330;
            }



            if(key[KEY_W])
            {
                setay = 260;
            }
            if(setay == 260 && key[KEY_ENTER])
                {
                    m = 0;
                    END_OF_FUNCTION(menu);

                }
            if(setay == 330 && key[KEY_ENTER])
                {


                   m = 2;
                }




    draw_sprite(buf, fundo, 0, 0);
    draw_sprite(buf, logo, 270, 40);
    textout_ex(buf, font, "Start Game", 310, 268, makecol(255,255,255), -1);
    textout_ex(buf, font, "Exit", 310, 338, makecol(255,255,255), -1);
    draw_sprite(buf, seta, 230, setay);
    draw_sprite(screen, buf, 0, 0);

    }
    destroy_bitmap(buf);
    destroy_bitmap(fundo);
    destroy_bitmap(seta);

    return m;
}



int main()
{
///iniciando
  allegro_init();
  install_timer();
  install_keyboard();
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
  set_window_title("Naruto");

  exit_program = FALSE;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  timer = 0;
  LOCK_FUNCTION(incrementa_timer);
  LOCK_VARIABLE(timer);
  install_int_ex(incrementa_timer, SECS_TO_TIMER(1));


  milisegundos = 0;
  LOCK_FUNCTION(msec_counter);
  LOCK_VARIABLE(milisegundos);
  install_int_ex(msec_counter, MSEC_TO_TIMER(1));

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

  BITMAP* naruto[11];
  naruto[0] = load_bitmap("andou1.bmp", NULL);
  naruto[1] = load_bitmap("andou2.bmp", NULL);
  naruto[2] = load_bitmap("andou3.bmp", NULL);
  naruto[3] = load_bitmap("andou4.bmp", NULL);
  naruto[4] = load_bitmap("andou5.bmp", NULL);
  naruto[5] = load_bitmap("andou6.bmp", NULL);
  naruto[6] = load_bitmap("andou7.bmp", NULL);
  naruto[7] = load_bitmap("andou8.bmp", NULL);
  naruto[8] = load_bitmap("parado.bmp", NULL);
  naruto[9] = load_bitmap("pulando.bmp", NULL);
  naruto[10] = load_bitmap("murro_4.bmp", NULL);



  BITMAP* sky = load_bitmap("sky.bmp", NULL);
  BITMAP* montanha = load_bitmap("montanha_hokage.bmp", NULL);
  BITMAP* cenario[8];
  for(int i =0; i<8;i++){cenario[i] = load_bitmap("cenario.bmp", NULL);}

  BITMAP* bloco = load_bitmap("bloco.bmp", NULL);

  BITMAP* manda[3];
  manda[0] = load_bitmap("manda.bmp", NULL);
  manda[1] = load_bitmap("manda2.bmp", NULL);
  manda[2] = load_bitmap("nada.bmp", NULL);

  BITMAP* vida[11];
  vida[10] = load_bitmap("vida_cheia.bmp", NULL);
  vida[9] = load_bitmap("vida_9.bmp", NULL);
  vida[8] = load_bitmap("vida_8.bmp", NULL);
  vida[7] = load_bitmap("vida_7.bmp", NULL);
  vida[6] = load_bitmap("vida_6.bmp", NULL);
  vida[5] = load_bitmap("vida_5.bmp", NULL);
  vida[4] = load_bitmap("vida_4.bmp", NULL);
  vida[3] = load_bitmap("vida_3.bmp", NULL);
  vida[2] = load_bitmap("vida_2.bmp", NULL);
  vida[1] = load_bitmap("vida_1.bmp", NULL);
  vida[0] = load_bitmap("vida_vazia.bmp", NULL);

  ///Variaveis
  float eixo_x = 0.0;
  float eixo_x_personagem = 250.0;
  float larg_pers = 80.0;
  float alt_pers = 80.0;
  float alt_bloco = 60.0;
  float larg_bloco = 60.0;
  float vel_x = 1.0;
  int num_frames = 8;
  int frame_atual = 0;
  int tempo_troca = 90;
  double direcao;
  int num_manda = 2;
  int frame_manda = 0;
  int frame_vida = 10;
  int cobra1 = 0;



   int marcador = timer; // MARCADOR DE TEMPO

    menu();
    if(m==2)
    {
        fecha_programa();
    }

  ///GAME LOOP
  while(!exit_program)
  {
     //CONTROLES

          if(key[KEY_ESC])
          {
              menu();
              if(m==2)
              {
                  fecha_programa();
              }
          }

         if(key[KEY_D])
         {
            frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
            direcao = DRAW_SPRITE_NO_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)


            eixo_x = eixo_x - vel_x; // FAZ O CENARIO ANDAR (QUE DA A IMPRESSÃO DO NARUTO ESTA SE MOVENDO)
         }
         else if(key[KEY_A])
         {
             frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
             direcao = DRAW_SPRITE_H_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)

            eixo_x = eixo_x + vel_x; // FAZ O CENARIO ANDAR (QUE DA A IMPRESSÃO DO NARUTO ESTA SE MOVENDO)
         }

         else
         {
             frame_atual = 8; // FRAME DO NARUTO PARADO


         }

          if(key[KEY_SPACE])
         {
             frame_atual = 10;
         }

         if(key[KEY_W]&& eixo_y > 80) // PULO
         {


                vel_y = -3;
                frame_atual = 9;
                vel_y += gravidade; eixo_y += vel_y;

         }


        // COLISÃO
        if(colidir(250, eixo_y, eixo_x+860, 240, 50, 80, 255, 1)) ////COLISÃO 1ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 175){eixo_y = 175;}
            }

        }
        else if (colidir(250, eixo_y, eixo_x+1760, 330, 50, 80, 360, 1)) //COLISÃO 2ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 280){eixo_y = 280;}}
        }
        else if (colidir(250, eixo_y, eixo_x+2229, 254, 50, 80, 300, 1)) //COLISÃO 3ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 220){eixo_y = 220;}}
        }
        else if (colidir(250, eixo_y, eixo_x+2950, 200, 50, 80, 600, 1)) //COLISÃO 4ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 130){eixo_y = 130;}}
        }
        else if (colidir(250, eixo_y, eixo_x+4250, 155, 50, 80, 120, 1)) //COLISÃO 5ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 105){eixo_y = 105;}}
        }
        else if (colidir(250, eixo_y, eixo_x+5400, 250, 50, 80, 200, 1)) //COLISÃO 6ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 200){eixo_y = 200;}}
        }
        else{vel_y += gravidade; eixo_y += vel_y;} // FUNÇÃO DE GRAVIDADE

    if(cobra1 != 2){frame_manda = (milisegundos / 900) % num_manda;
        if(colidir(250, eixo_y, eixo_x+1015, 140, 50, 80, 150, 150)) ////COLISÃO 1ª COBRA
        {
            if(eixo_x<=-709 && eixo_x>=-730){eixo_x = -709;} // BLOQUEIA A PASSAGEM PELA FRENTE DA COBRA
            else if(eixo_x>=-860 && eixo_x<=-740){eixo_x = -860;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA
            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_manda = 2;
                cobra1 = 2;

            }

            else if(timer - marcador >=2){frame_vida--; marcador = timer;} // SERVE PARA NÃO FICAR PERDENDO VIDA CONTINUAMENTE
        }
    }



         //CONDIÇÕES


         if(eixo_x<-5600)
         {
             eixo_x = -5600; // PONTO FINAL DO EIXO X
         }
         if(eixo_x>0)
         {
             eixo_x = 0; // PONTO INICIAL DO EIXO X
         }


         if(eixo_y > 460.0)
         {
             eixo_y = 460.0; // PONTO FINAL EIXO Y
         }






         //DRAW

         draw_sprite(buffer, sky, 0, 0);
         draw_sprite(buffer, montanha, 0, 0);
         draw_sprite(buffer, cenario[0], eixo_x, 10); //PRIMEIRO CENARIO
         for(int c = 1; c<8; c++){draw_sprite(buffer, cenario[c], eixo_x+800*c, 10);} // REPETIÇÃO DO CENARIO
         for(int b = 0; b<5; b++){draw_sprite(buffer, bloco, eixo_x+850+(60*b), 265);} //1ª SERIE DE BLOCOS
         for(int b = 0; b<7; b++){draw_sprite(buffer, bloco, eixo_x+1750+(60*b), 365);} //2ª SERIE DE BLOCOS
         for(int b = 0; b<6; b++){draw_sprite(buffer, bloco, eixo_x+2229+(60*b), 304);} //3ª SERIE DE BLOCOS
         for(int b = 0; b<11; b++){draw_sprite(buffer, bloco, eixo_x+2900+(60*b), 225);} //4ª SERIE DE BLOCOS
         for(int b = 0; b<3; b++){draw_sprite(buffer, bloco, eixo_x+4200+(60*b), 185);} //5ª SERIE DE BLOCOS
         for(int b = 0; b<5; b++){draw_sprite(buffer, bloco, eixo_x+5350+(60*b), 300);} //6ª SERIE DE BLOCOS
         draw_sprite_ex(buffer, manda[frame_manda], eixo_x+1015, 140, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//1ª COBRA
         draw_sprite_ex(buffer, naruto[frame_atual], eixo_x_personagem, eixo_y, DRAW_SPRITE_NORMAL, direcao);//PERSONAGEM
         draw_sprite(buffer, vida[frame_vida], 30, 50);
         textout_ex(buffer, font, "Vida", 40, 40, makecol(255,255,255), -1);
         draw_sprite(screen, buffer, 0, 0);




  }

  ///FINALIZAÇÃOs
  destroy_bitmap(buffer);
  destroy_bitmap(naruto);
  destroy_bitmap(sky);
  destroy_bitmap(montanha);
  destroy_bitmap(cenario);
  destroy_bitmap(bloco);
  destroy_bitmap(manda);


  return 0;
}
END_OF_MAIN();

///FUNÇÃO COLISÃO
int colidir(int ax, int ay, int bx, int by, int aw, int ah, int bw, int bh){
    if(ax+aw>bx && ax<bx+bw && ay+ah >by && ay<by+bh)return 1; // AX = EIXO X DO PERSONAGEM; AY = EIXO Y DO PERSONAGEM; BX = EIXO X DO OBJETO; BY = EIXO Y DO OBJETO; AW = LARGURA DO PERSONAGEM; AH = ALTURA DO PERSONAGEM; BW = LARGURA DO OBJETO; BH = ALTURA DO OBJETO

    return 0;}








