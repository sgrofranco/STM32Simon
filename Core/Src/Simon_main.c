/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main_Modelo_2023.c
 * @brief          : Untref_IC_2022_3
 * 2022_3
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
char time[12];
char date[12];
char buffer1[30];
char hora = 23;
char minuto = 59;
char segundo = 55;
char anio = 23;    		//año 2022 -> 00010110
char mes = 9;     		//mes enero-> 00000001 (1) .... dici-> 00001100 (12)
char diasem = 0;   		//1 Lun , 2 Mar......, 0 Dom
char dia = 24;      	//dia 01 -> 00000001.....31 -> 00011111
char Alarma_hora = 0;
char Alarma_min = 0;
char Alarma_seg = 0;
char Estado = 0;
char Tecla = 0;
char count1 = 80;
char Enter_Esc_flag = 0;
char Limite_dia_decena = 4;
char Limite_dia_unidad = 9;
int AD_RES = 0;

char nivelJuego = 1;
int nivel = 0;
int usuarioJugando = 0;
int dificultad = 1;

uint8_t secuencia[10];
uint8_t secuenciaSize = 1;
uint8_t secuenciaUsuario[10];
uint8_t secuenciaUsuarioSize = 1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC1_Init(void);

/* USER CODE BEGIN PFP */
void Delay_useg(uint32_t timer);
char conv_int_hex(char cih);
void lcd_init(void);
void lcd_send_cmd(char cmd);
void send_to_lcd(char data, int rs);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_put_cur(int row, int col);
void lcd_clear(void);
void send_lcd_ASCII(char data);
static void set_reloj(void);
void get_time(void);
void Display_DiaHora(void);
void Teclado(void);
void Validador_dia(void);
void ConversorAD(void);
static void actualizarReloj(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_RTC_Init();
	MX_TIM3_Init();
	MX_ADC1_Init();
	/* USER CODE BEGIN 2 */
#define Alarma_On    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
#define Alarma_Off   	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
#define Row1_On      	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
#define Row1_Off    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
#define Row2_On      	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
#define Row2_Off     	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
#define Row3_On      	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
#define Row3_Off     	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
#define Row4_On      	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
#define Row4_Off     	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
#define Column1_On   	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==1
#define Column1_Off  	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==0
#define Column2_On   	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)==1
#define Column2_Off  	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)==0
#define Column3_On   	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==1
#define Column3_Off  	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==0
#define Column4_On   	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==1
#define Column4_Off  	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==0
#define Led_Az_On    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
#define Led_Az_Off   	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
#define Led_Rj_On    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
#define Led_Rj_Off   	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
#define Led_Am_On    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
#define Led_Am_Off   	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
#define Led_Vd_On    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
#define Led_Vd_Off   	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

#define Switch_Az_On  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==0
#define Switch_Az_Off HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1
#define Switch_Rj_On  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)==0
#define Switch_Rj_Off HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)==1
#define Switch_Am_On  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)==0
#define Switch_Am_Off HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)==1
#define Switch_Vd_On  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)==0
#define Switch_Vd_Off HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)==1

	/*********** Define the LCD PINS below ****************/
#define RS_Pin 			GPIO_PIN_15
#define RS_GPIO_Port 		GPIOA
	//#define RW_Pin 			GPIO_PIN_2
	//#define RW_GPIO_Port 	GPIOA
#define EN_Pin 			GPIO_PIN_5
#define EN_GPIO_Port 		GPIOA
#define D4_Pin 			GPIO_PIN_3
#define D4_GPIO_Port 		GPIOB
#define D5_Pin 			GPIO_PIN_4
#define D5_GPIO_Port 		GPIOA
#define D6_Pin 			GPIO_PIN_5
#define D6_GPIO_Port 		GPIOB
#define D7_Pin 			GPIO_PIN_3
#define D7_GPIO_Port 		GPIOA

	/*
	 ******************************************************************************
	 * Display commands
	 *
	 * lcd_init ();
	 * lcd_clear ();
	 * lcd_put_cur(Row, Col);  	// Position  (0, 0) --> Home position
	 * lcd_send_string("HOLA MUNDO");
	 * send_lcd_ASCII (238);		// ñ letter for ASCII caracter
	 * lcd_send_cmd(0x02);  		// Return Home
	 * lcd_send_cmd(0x00);  		// Display Off
	 * lcd_send_cmd(0x08);  		// Display On
	 * lcd_send_cmd(0x0C);  		// Cursor Off  Blink Off
	 * lcd_send_cmd(0x0E);  		// Cursor On   Blink Off
	 * lcd_send_cmd(0x0D);  		// Cursor Off  Blink On
	 * lcd_send_cmd(0x0F);  		// Cursor On   Blink On
	 * lcd_send_cmd(0x06);  		// Position to Right  Display fix
	 * lcd_send_cmd(0x04);  		// Position to Left   Display fix
	 * lcd_send_cmd(0x07);  		// Position to Right  Cursor fix
	 * lcd_send_cmd(0x05);  		// Position to Left   Cursor fix
	 * lcd_send_cmd(0x10);  		// Cursor move to left
	 * lcd_send_cmd(0x14);  		// Cursor move to right
	 * lcd_send_cmd(0x18);  		// Display move to left
	 * lcd_send_cmd(0x1C);  		// Display move to right
	 ******************************************************************************
	 */
	lcd_init();
	set_reloj();
	HAL_ADCEx_Calibration_Start(&hadc1);// Calibrate The ADC On Power-Up For Better Accuracy

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		Teclado();
		//ConversorAD ();
		if (Switch_Vd_On) {
			Led_Vd_On
			;
		} else {
			Led_Vd_Off
			;
		}  	// Código para probar switches
		if (Switch_Rj_On) {
			Led_Rj_On
			;
		} else {
			Led_Rj_Off
			;
		}
		if (Switch_Am_On) {
			Led_Am_On
			;
		} else {
			Led_Am_Off
			;
		}
		if (Switch_Az_On) {
			Led_Az_On
			;
		} else {
			Led_Az_Off
			;
		}

		switch (Estado) {
		case 0: {											//Estado permanente
			char cambiaseg = segundo;
			get_time();
			if (cambiaseg != segundo) {
				Display_DiaHora();
			}
			if (Tecla == 11) {
				Estado = 1;
			}					// Tecla A presionada
			if (Tecla == 12) {
				Estado = 2;
			}					// Tecla B presionada
			if (Tecla == 14) {
				Estado = 3;
			}					// Tecla D presionada
			Tecla = 0;
		}
			break;

		case 1: {										//Estado 1
			lcd_put_cur(0, 0);
			lcd_send_string("Fecha:  ");
			lcd_send_string(date);
			lcd_put_cur(1, 0);
			lcd_send_string("Hora:   ");
			lcd_send_string(time);

			int posicion = 0;
			char dateTerminada = 0;
			while (posicion < 15) {
				lcd_send_cmd(0x0D);

				Teclado();

				if (Tecla) {
					if (dateTerminada) {
						time[posicion] = Tecla;
					} else {
						date[posicion] = Tecla;
					}
					posicion++;
					if (posicion == 2 || posicion == 5) {
						posicion++;
					}
				}

				if (posicion == 9) {
					dateTerminada = 1;
					posicion = 0;
				}

				if (dateTerminada) {
					lcd_put_cur(1, 8);
					lcd_send_string(time);
				} else {
					lcd_put_cur(0, 8);
					lcd_send_string(date);
				}

				if (Tecla == 16 || Tecla == 15) { // Tecla * presionada, regresar al estado anterior
					lcd_send_cmd(0x0C);
					break;
				}

				Tecla = 0;
				HAL_Delay(200);
			}
			if (Tecla == 16) { // Tecla # presionada, regresar al estado anterior
				Estado = 0;
				lcd_clear();
				actualizarReloj();
				set_reloj();
			}

			if (Tecla == 15) { // Tecla * presionada, regresar al estado anterior
				Estado = 0;
				lcd_clear();
			}

			Tecla = 0;
		}
			break;
		case 2: {								//Estado programacion año decena
			lcd_clear();
			count1 = 10;
			Estado = 0;
			Tecla = 0;
			lcd_put_cur(0, 0);
			lcd_send_string("Dificultad:      ");
			//lcd_put_cur(0,13);
			//sprintf(buffer1, "%02u ", dificultad);
			//lcd_send_string(buffer1);
			while (count1) {
				int dificultad_change = dificultad;
				ConversorAD();
				if (dificultad < 1) {
					dificultad = 1;
				}
				if (dificultad_change != dificultad) {
					count1 = 30;
				}
				Teclado();
				if (Tecla == 15) {
					count1 = 1;
					Enter_Esc_flag = 0;
					Estado = 0;
				}
				lcd_put_cur(0, 13);
				sprintf(buffer1, "%02u ", dificultad);
				lcd_send_string(buffer1);
				lcd_put_cur(1, 0);
				switch (dificultad) {
				case 1: {
					lcd_send_string("#               ");
					break;
				}
				case 2: {
					lcd_send_string("##              ");
					break;
				}
				case 3: {
					lcd_send_string("###             ");
					break;
				}
				case 4: {
					lcd_send_string("####            ");
					break;
				}
				case 5: {
					lcd_send_string("#####           ");
					break;
				}
				case 6: {
					lcd_send_string("######          ");
					break;
				}
				case 7: {
					lcd_send_string("#######        ");
					break;
				}
				case 8: {
					lcd_send_string("########        ");
					break;
				}
				case 9: {
					lcd_send_string("#########       ");
					break;
				}
				case 10: {
					lcd_send_string("##########      ");
					break;
				}
				case 11: {
					lcd_send_string("###########     ");
					break;
				}
				case 12: {
					lcd_send_string("############    ");
					break;
				}
				case 13: {
					lcd_send_string("#############   ");
					break;
				}
				case 14: {
					lcd_send_string("##############  ");
					break;
				}
				case 15: {
					lcd_send_string("############### ");
					break;
				}

				}
				Tecla = 0;
				count1--;
			}
			lcd_clear();
			break;
			case 3:
			{
				nivelJuego = 1;
				nivel = 1;
				while (nivelJuego) {
					lcd_put_cur(0, 0);
					lcd_send_string("JUGANDO SIMON   ");
					lcd_put_cur(1, 0);
					sprintf(buffer1, "Nivel: %01u       ", nivelJuego);
					lcd_send_string(buffer1);
					HAL_Delay(100);
					generarSecuencia(secuencia, secuenciaSize);
					mostrarSecuencia(secuencia, secuenciaSize);
					usuarioJugando = 1;
					while (usuarioJugando) {
						lcd_put_cur(0, 0);
						lcd_send_string("JUGA            ");
						leerInputUsuario(secuenciaUsuario,
								secuenciaUsuarioSize);
						usuarioJugando = 0;
					}
					uint8_t correcto = 1;
					for (uint8_t i = 0; i < secuenciaSize; i++) {
						if (secuenciaUsuario[i] != secuencia[i]) {
							correcto = 0;
							break;
						}
					}

					if (correcto) {
						// SECUECNIA CORRECTA
						lcd_put_cur(0, 0);
						lcd_send_string("BIEN HECHO!      ");
						HAL_Delay(1000);

						lcd_clear();
						nivelJuego++;
						nivel++;
						secuenciaSize++;
						secuenciaUsuarioSize++;

					} else {
						// ¨PERDISTE
						nivel = 1;
						lcd_put_cur(0, 0);
						lcd_send_string("PERDISTE        ");
						lcd_put_cur(1, 0);
						printf(buffer1, "Nivel: %01u         ", nivelJuego);
						nivelJuego = 0;
						lcd_send_string(buffer1);
						secuenciaSize = 1;
						secuenciaUsuarioSize = 1;

					}
				}
				Estado = 4;
			}
			lcd_clear();
			break;
			case 4:
			{
				lcd_put_cur(0, 0);
				lcd_send_string("GAME OVER      ");
				while (Estado == 4) {
					Teclado();
					if (Tecla == 15) {
						Estado = 0;
						break;
					}
					if (Tecla == 14) {
						Estado = 0;
						break;
					}
					Tecla = 0;
				}
			}
			break;

		}
		}

	}
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_ADC;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
	HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void) {

	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */

	/** Common config
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC1_Init 2 */

	/* USER CODE END ADC1_Init 2 */

}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void) {

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef DateToUpdate = { 0 };

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */

	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
	hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = 0x0;
	sTime.Minutes = 0x0;
	sTime.Seconds = 0x0;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
	DateToUpdate.Month = RTC_MONTH_JANUARY;
	DateToUpdate.Date = 0x1;
	DateToUpdate.Year = 0x0;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void) {

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */
	HAL_TIM_MspPostInit(&htim3);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
			GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11
					| GPIO_PIN_15, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			GPIO_PIN_0 | GPIO_PIN_10 | GPIO_PIN_15 | GPIO_PIN_3 | GPIO_PIN_4
					| GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_13,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : PA0 PA3 PA4 PA5
	 PA11 PA12 PA15 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
			| GPIO_PIN_11 | GPIO_PIN_15 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PA1 PA2 */
	GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB10 PB15 PB3 PB4
	 PB5 PB8 PB9 PB2 PB13 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_10 | GPIO_PIN_15 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_2
			| GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PB11 PB12 PB14 */
	GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PA8 */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : PA9 */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PA6 PA10 */
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB6 PB7 */
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Delay_useg(uint32_t timer) {
	timer = timer / 1.5;
	while (timer--) {
		__ASM volatile ("NOP");
	}
}

char conv_int_hex(char cih) {
	char x = 0;
	if (cih < 16) {
		x = cih;
	} else if (cih < 20) {
		x = cih + 6;
	} else if (cih < 30) {
		x = cih + 12;
	} else if (cih < 40) {
		x = cih + 18;
	} else if (cih < 50) {
		x = cih + 24;
	} else if (cih < 60) {
		x = cih + 30;
	};
	return x;
}

void lcd_init(void) {
// 4 bit initialisation
	HAL_Delay(50);  			// wait for >40ms
	lcd_send_cmd(0x0F);		// BLINK ON
	HAL_Delay(5);  				// wait for >4.1ms
	lcd_send_cmd(0b10000010);	// 4bit mode
	HAL_Delay(5);  				// wait for >4.1ms
	lcd_send_cmd(0x01);  		// clear display
	HAL_Delay(5);  				// wait for >4.1ms
	lcd_send_cmd(0b00000010);	// Position home
	HAL_Delay(5);  				// wait for >4.1ms
	lcd_send_cmd(0b00001100);	// Cursor->off  Blinking->off
	HAL_Delay(5);  				// wait for >4.1ms
//lcd_send_cmd (0x06); 		//Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	lcd_send_cmd(0x28);		// 4 BIT  2 LINES  5X7
	HAL_Delay(5);
}

void lcd_send_cmd(char cmd) {
	char datatosend;

	/* send upper nibble first */
	datatosend = ((cmd >> 4) & 0x0f);
	send_to_lcd(datatosend, 0);  // RS must be 0 while sending command

	/* send Lower Nibble */
	datatosend = ((cmd) & 0x0f);
	send_to_lcd(datatosend, 0);
}

void send_lcd_ASCII(char data) {
	char datatosend;

	/* send higher nibble */
	datatosend = ((data >> 4) & 0x0f);
	send_to_lcd(datatosend, 1);  // rs =1 for sending data

	/* send Lower nibble */
	datatosend = ((data) & 0x0f);
	send_to_lcd(datatosend, 1);
}

void send_to_lcd(char data, int rs) {
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs); // rs = 1 for data, rs=0 for command

	/* write the data to the respective pin */
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, ((data >> 3) & 0x01));
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, ((data >> 2) & 0x01));
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, ((data >> 1) & 0x01));
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, ((data >> 0) & 0x01));

	/* Toggle EN PIN to send the data
	 * if the HCLK > 100 MHz, use the  20 us delay
	 * if the LCD still doesn't work, increase the delay to 50, 80 or 100..
	 */
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
	HAL_Delay(2);
	Delay_useg(10);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
	HAL_Delay(2);
	Delay_useg(10);
}

void lcd_send_data(char data) {
	char datatosend;

	/* send higher nibble */
	datatosend = ((data >> 4) & 0x0f);
	send_to_lcd(datatosend, 1);  // rs =1 for sending data

	/* send Lower nibble */
	datatosend = ((data) & 0x0f);
	send_to_lcd(datatosend, 1);
}

void lcd_send_string(char *str) {
	while (*str)
		lcd_send_data(*str++);
}

void lcd_put_cur(int row, int col) {
	char Fil_Col = 128;
	if (col > 15) {
		col = 15;
	}
	switch (row) {
	case 0:
		Fil_Col = 128 + col;
		break;
	case 1:
		Fil_Col = 192 + col;
		break;
	case 2:
		Fil_Col = 148 + col;
		break;
	case 3:
		Fil_Col = 212 + col;
		break;
	default:
		break;
	}
	lcd_send_cmd(Fil_Col);
}

void lcd_clear(void) {
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

static void set_reloj(void) {
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef DateToUpdate = { 0 };
	RTC_AlarmTypeDef sAlarm = { 0 };

	hrtc.Instance = RTC;
	hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
	hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}

	sTime.Hours = conv_int_hex(hora);
	sTime.Minutes = conv_int_hex(minuto);
	sTime.Seconds = conv_int_hex(segundo);

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
//DateToUpdate.WeekDay = diasem;
	DateToUpdate.Month = conv_int_hex(mes);
	DateToUpdate.Date = conv_int_hex(dia);
	DateToUpdate.Year = conv_int_hex(anio);

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
// Enable the Alarm A

	sAlarm.AlarmTime.Hours = conv_int_hex(Alarma_hora);
	sAlarm.AlarmTime.Minutes = conv_int_hex(Alarma_min);
	sAlarm.AlarmTime.Seconds = conv_int_hex(Alarma_seg);
	sAlarm.Alarm = RTC_ALARM_A;
	if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
}

void get_time(void) {
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	/* Display time Format: hh:mm:ss */
	hora = gTime.Hours;
	minuto = gTime.Minutes;
	segundo = gTime.Seconds;
	sprintf(time, "%02u:%02u:%02u", hora, minuto, segundo);
	/* Display date Format: dd-mm-yy */
	diasem = gDate.WeekDay;
	dia = gDate.Date;
	mes = gDate.Month;
	anio = gDate.Year;
	sprintf(date, "%02u/%02u/%02u", dia, mes, anio);
}

/*

 void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
 {
 Alarma_On; // turn on the LED
 }*/

void Display_DiaHora(void) {
	lcd_put_cur(0, 0);
	switch (diasem) {
	case 0: {
		lcd_send_string("Domingo ");
	}
		break;
	case 1: {
		lcd_send_string("Lunes   ");
	}
		break;
	case 2: {
		lcd_send_string("Martes  ");
	}
		break;
	case 3: {
		lcd_send_string("Miercol ");
	}
		break;
	case 4: {
		lcd_send_string("Jueves  ");
	}
		break;
	case 5: {
		lcd_send_string("Viernes ");
	}
		break;
	case 6: {
		lcd_send_string("Sabado  ");
	}
		break;
	}
	lcd_put_cur(0, 8);  			// Position  (Fila,Columna)
	lcd_send_string(date);
	lcd_put_cur(1, 0);  			// Position  (Fila,Columna)
	lcd_send_string(time);
	lcd_put_cur(1, 8);  			// Position  (Fila,Columna)
}

void Teclado(void) {
	Tecla = 0;
	Row1_On
	;
	Row2_Off
	;
	Row3_Off
	;
	Row4_Off
	;
	HAL_Delay(20);
	if (Column1_On) {
		Tecla = '1';
	}
	if (Column2_On) {
		Tecla = '2';
	}
	if (Column3_On) {
		Tecla = '3';
	}
	if (Column4_On) {
		Tecla = 11;
	}
	Row1_Off
	;
	Row2_On
	;
	Row3_Off
	;
	Row4_Off
	;
	HAL_Delay(20);
	if (Column1_On) {
		Tecla = '4';
	}
	if (Column2_On) {
		Tecla = '5';
	}
	if (Column3_On) {
		Tecla = '6';
	}
	if (Column4_On) {
		Tecla = 12;
	}
	Row1_Off
	;
	Row2_Off
	;
	Row3_On
	;
	Row4_Off
	;
	HAL_Delay(20);
	if (Column1_On) {
		Tecla = '7';
	}
	if (Column2_On) {
		Tecla = '8';
	}
	if (Column3_On) {
		Tecla = '9';
	}
	if (Column4_On) {
		Tecla = 13;
	}
	Row1_Off
	;
	Row2_Off
	;
	Row3_Off
	;
	Row4_On
	;
	HAL_Delay(20);
	if (Column1_On) {
		Tecla = 15;
	}
	if (Column2_On) {
		Tecla = '0';
	}
	if (Column3_On) {
		Tecla = 16;
	}
	if (Column4_On) {
		Tecla = 14;
	}
	Row1_Off
	;
	Row2_Off
	;
	Row3_Off
	;
	Row4_Off
	;
}

void Validador_dia(void) {
	if ((anio == 24 || anio == 28 || anio == 32 || anio == 36 || anio == 40
			|| anio == 44 || anio == 48 || anio == 52 || anio == 56)
			&& mes == 2) {
		Limite_dia_decena = 3;
		Limite_dia_unidad = 10;
	} else if (mes == 2) {
		Limite_dia_decena = 3;
		Limite_dia_unidad = 9;
	}
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
		Limite_dia_decena = 4;
		if (dia > 29) {
			Limite_dia_unidad = 1;
		} else
			Limite_dia_unidad = 10;
	}
	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10
			|| mes == 12) {
		Limite_dia_decena = 4;
		if (dia > 29) {
			Limite_dia_unidad = 2;
		} else
			Limite_dia_unidad = 10;
	}
}

void ConversorAD(void) {

	HAL_ADC_Start(&hadc1);					// Start ADC Conversion
	HAL_ADC_PollForConversion(&hadc1, 1);// Poll ADC1 Perihperal & TimeOut = 1mSec
	AD_RES = HAL_ADC_GetValue(&hadc1);// Read The ADC Conversion Result & Map It To PWM DutyCycle
//TIM2->CCR1 = (AD_RES<<4);
//temp_medida = AD_RES/100.1;
	dificultad = AD_RES / 237;
}

static void actualizarReloj(void) {
	int diaInt = (date[0] - '0') * 10 + (date[1] - '0');
	int mesInt = (date[3] - '0') * 10 + (date[4] - '0');
	int anioInt = (date[6] - '0') * 10 + (date[7] - '0');

	if (diaInt < 1 || diaInt > 31 || mesInt < 1 || mesInt > 12 || anioInt < 0
			|| anioInt > 99) {
		lcd_put_cur(0, 0);
		lcd_send_string("  FECHA ERRONEA ");
		lcd_send_string(date);
		lcd_put_cur(1, 0);
		lcd_send_string("                ");
		return;
	}

	dia = diaInt;
	mes = mesInt;
	anio = anioInt;

	int horaInt = (time[0] - '0') * 10 + (time[1] - '0');
	int minutoInt = (time[3] - '0') * 10 + (time[4] - '0');
	int segundoInt = (time[6] - '0') * 10 + (time[7] - '0');

	if (horaInt < 0 || horaInt > 23 || minutoInt < 0 || minutoInt > 59
			|| segundoInt < 0 || segundoInt > 59) {
		lcd_put_cur(0, 0);
		lcd_send_string("  HORA ERRONEA  ");
		lcd_send_string(date);
		lcd_put_cur(1, 0);
		lcd_send_string("                ");
		return;
	}

	hora = horaInt;
	minuto = minutoInt;
	segundo = segundoInt;
}

void generarSecuencia(uint8_t secuencia[], uint8_t largo) {

	for (uint8_t i = largo - 1; i < largo; i++) {
		secuencia[i] = rand() % 4;
	}
}

void mostrarSecuencia(const uint8_t secuencia[], uint8_t largo) {

	for (uint8_t i = 0; i < largo; i++) {
		switch (secuencia[i]) {
		case 0:
			Led_Vd_On
			; // VERDE
			break;
		case 1:
			Led_Rj_On
			; // ROJO
			break;
		case 2:
			Led_Az_On
			; // AZUL
			break;
		case 3:
			Led_Am_On
			; // AMARILLO
			break;
		}
		HAL_Delay(2000 / (2 + nivel + dificultad));

		Led_Am_Off
		;
		Led_Az_Off
		;
		Led_Rj_Off
		;
		Led_Vd_Off
		;

		HAL_Delay(2000 / (1 + nivel + dificultad));

	}
}

int compararTiempo(uint32_t tiempoInicio) {
	return HAL_GetTick() - tiempoInicio < 3000;
}

void leerInputUsuario(uint8_t secuecniaUsuario[], uint8_t largo) {
	uint32_t tiempoInicio = HAL_GetTick();
	while (compararTiempo(tiempoInicio)) {
		for (uint8_t i = 0; i < largo; i++) {

			while (Switch_Am_On != GPIO_PIN_SET && Switch_Az_On != GPIO_PIN_SET
					&&
					Switch_Rj_On != GPIO_PIN_SET && Switch_Vd_On != GPIO_PIN_SET
					&& compararTiempo(tiempoInicio)) {

			}

			if ( Switch_Vd_On) {
				Led_Vd_On
				;
				secuecniaUsuario[i] = 0; // VERDE
				HAL_Delay(100);
				Led_Vd_Off
			}
			if ( Switch_Rj_On) {
				Led_Rj_On
				;
				secuecniaUsuario[i] = 1; // ROJO
				HAL_Delay(100);
				Led_Rj_Off
			}
			if ( Switch_Az_On) {
				Led_Az_On
				;
				secuecniaUsuario[i] = 2; // AZUL
				HAL_Delay(100);
				Led_Az_Off
			}
			if ( Switch_Am_On) {
				Led_Am_On
				;
				secuecniaUsuario[i] = 3; // AMARILLO
				HAL_Delay(100);
				Led_Am_Off
			}

			while (Switch_Vd_On == GPIO_PIN_SET ||
			Switch_Az_On == GPIO_PIN_SET ||
			Switch_Rj_On == GPIO_PIN_SET ||
			Switch_Am_On == GPIO_PIN_SET) {

			}
		}
		break;
	}
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
