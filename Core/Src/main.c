/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "57.h"
#include <stdio.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
__IO bool rxFrameFlag = false;
uint8_t step[13]={0x01,0xFD,0x00,0x03,0xE8,0xB0,0x00,0x00,0x00,0x00,0x01,0x00,0x6B};
uint8_t mea[5]={0xA5,0x5A,0x04,0x00,0xFB};
uint8_t out[15]={0xAB,0xBA,0x00,0x7c,0x00,0x80,0x00,0x73,0x00,0xF3};
uint8_t Angle1[10],n1=10,d,RX01,rou[360];
int angle=0,i=0;
int R,Rmax,Rmin,Routside[360];
#define pi 3.141592
     float Rceliangbi=250;
     float Rinside[360];
     float x[360],y[360];
     float Rpoint[360];
     float Rlixiang;
     float A0=0,A1=0,B0=0,B1=0,C0=0,C1=0,C2=0,D0=0,E0=0,E1=0;
     float A=0,B=0,C=0,D=0,E=0;
     float Aw=0,Bw=0,Cw=0,Dw=0,Ew=0;
    float a,b,c,e;
     float Ox,Oy;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void test()

{

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(2000);
	HAL_UART_Transmit(&huart2,(uint8_t *)step,13,HAL_MAX_DELAY);

	HAL_Delay(500);
	HAL_UART_Transmit(&huart1,(uint8_t *)mea,5,HAL_MAX_DELAY);
		HAL_Delay(500);
	HAL_UART_Receive_IT(&huart1,&RX01,1); 
	HAL_Delay(5000);
	
	for (i=1;i<=360;i++)
	{
		angle=27.7*i;
		
		
		
		step[6]=(angle >> 24); 
		step[7]=(angle >> 16); 
		step[8]=(angle >> 8); 
		step[9]=(angle >> 0); 
		HAL_UART_Transmit(&huart2,(uint8_t *)step,13,HAL_MAX_DELAY);
		
		HAL_Delay(500);
		Routside[i-1]=d;
	}

  
         for(i=0;i<360;i++) 
         {
           Rinside[i]=Rceliangbi-Routside[i];
           x[i]=Rinside[i]*cos(i*pi/180);
           y[i]=Rinside[i]*sin(i*pi/180);
        }
        
        int k;
        for(k=0;k<360;k++)
        {
          A0=A0+x[k]*x[k];
          A1=A1+x[k];
          B0=B0+x[k]*y[k];
          B1=B1+y[k];
          C0=C0+x[k]*x[k]*x[k];
          C1=C1+x[k]*y[k]*y[k];
          C2=C2+x[k]*x[k]+y[k]*y[k];
          D0=D0+y[k]*y[k];
          E0=E0+x[k]*x[k]*y[k];
          E1=E1+y[k]*y[k]*y[k];
        }

          Aw=360*A0;
          Bw=360*B0;
          Cw=360*C0+360*C1;
          Dw=360*D0;
          Ew=360*E0+360*E1;

          A=Aw-A1*A1;
          B=Bw-A1*B1;
          C=Cw-C2*A1;
          D=Dw+B1*B1;
          E=Ew+C2*B1;

             a=(B*E-C*D)/(A*D-B*B);
             b=(A*E-B*C)/(A*D-B*B);
             c=-(C2+a*A1+b*B1)/360;
    
      Ox=-a/2;
      Oy=-b/2;
      d=a*a/4;
      e=b*b/4;
      R=sqrt((a*a/4)-(b*b/4)-c);

      int j;
      for(j=0;j<360;j++)
      {
        Rpoint[j]=sqrt((x[j]-Ox)*(x[j]-Ox)+(y[j]-Oy)*(y[j]-Oy));
      }

      int n;
      Rmax=Rmin=Rpoint[0];
      for(n=1;n<360;n++)
      {
        if(Rpoint[n]>Rmax)
        {
          Rmax=Rpoint[n];
        }
        if(Rpoint[n]<Rmin)
        {
          Rmin=Rpoint[n];
        }
      }

			
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//HAL_Delay(200);
//HAL_UART_Transmit(&huart3,(uint8_t *)out,15,HAL_MAX_DELAY);
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
 if(huart== &huart1) 
 {
    if((RX01==0xB4)&&(n1>8))  //判断帧头
	  {
   		n1=0;
  	}
  	if(n1<8)//有几位就接收几位，从零开始
  	{
	    Angle1[n1]=RX01;
	  	n1++;
	  }
	  if(n1==8)
  	{	
			
	  d=(Angle1[5]<<8)|Angle1[6];
    	   n1++;             
    }
  	HAL_UART_Receive_IT(&huart1,&RX01,5); 
	}
  
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
