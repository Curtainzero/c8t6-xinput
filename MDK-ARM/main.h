#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LeftStickVer_Pin GPIO_PIN_0
#define LeftStickVer_GPIO_Port GPIOA
#define LeftStickHori_Pin GPIO_PIN_1
#define LeftStickHori_GPIO_Port GPIOA
#define LeftTrigger_Pin GPIO_PIN_2
#define LeftTrigger_GPIO_Port GPIOA
#define RightTrigger_Pin GPIO_PIN_3
#define RightTrigger_GPIO_Port GPIOA
#define RightStickHori_Pin GPIO_PIN_4
#define RightStickHori_GPIO_Port GPIOA
#define RightStickVer_Pin GPIO_PIN_5
#define RightStickVer_GPIO_Port GPIOA
#define A_Pin GPIO_PIN_7
#define A_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_0
#define B_GPIO_Port GPIOB
#define X_Pin GPIO_PIN_1
#define X_GPIO_Port GPIOB
#define Y_Pin GPIO_PIN_10
#define Y_GPIO_Port GPIOB
#define RB_Pin GPIO_PIN_11
#define RB_GPIO_Port GPIOB
#define Dright_Pin GPIO_PIN_12
#define Dright_GPIO_Port GPIOB
#define LB_Pin GPIO_PIN_13
#define LB_GPIO_Port GPIOB
#define Dup_Pin GPIO_PIN_14
#define Dup_GPIO_Port GPIOB
#define Ddown_Pin GPIO_PIN_15
#define Ddown_GPIO_Port GPIOB
#define Dleft_Pin GPIO_PIN_8
#define Dleft_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_9
#define LED_GPIO_Port GPIOA
#define L3_Pin GPIO_PIN_15
#define L3_GPIO_Port GPIOA
#define SELECT_Pin GPIO_PIN_3
#define SELECT_GPIO_Port GPIOB
#define START_Pin GPIO_PIN_4
#define START_GPIO_Port GPIOB
#define R3_Pin GPIO_PIN_5
#define R3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */