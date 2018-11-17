#ifndef PAUSEMENU_H
#define PAUSEMENU_H

void PauseMenu_Init();
void PauseMenu_Update();
void DrawBorder();
void DrawOptions();
void DrawToolTips(int);
void PointAtOption(int);
void PauseMenu_CheckInput();

#endif