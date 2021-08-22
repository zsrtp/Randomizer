#include "data/items.h"
#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_kankyo.h"
#include "tp/d_a_alink.h"
#include "tp/d_save.h"
#include "tp/d_com_inf_game.h"

#include <string.h>


namespace mod::game_patch
{
    int _01_getLayerNo(const char *stageName, int roomId, int layerOverride)
	{
		int chosenLayer;
		bool condition;

        libtp::tp::d_save::dSv_player_status_b_c* playerStatusBPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b;
	
		int stageComparison;
		unsigned int uVar2;

		chosenLayer = layerOverride;

		 if (layerOverride < 0) 
		 {
    		chosenLayer = -1;
			condition = libtp::tp::d_kankyo::dKy_darkworld_stage_check(stageName, roomId);
			if (condition == true) 
			{
				chosenLayer = 0xE;
			}
		 
			if (chosenLayer < 0xD) {
				//Snowpeak / Snowpeak Ruins
				stageComparison = strcmp(stageName, "D_MN11"); 
				if ((stageComparison == 0) || (stageComparison = strcmp(stageName, "F_SP114"), stageComparison == 0)) {
					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x10A]); //Snowpeak Ruins Completed
					if (condition == false) {
						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0xA3]); //Yeta unlocks the West door in SPR
						if (condition == false) {
							condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0xA2]); //Yeta unlocks the North-West door in SPR
							if (condition != false) {
								chosenLayer = 0x1;
							}
						}
						else {
							chosenLayer = 0x2;
						}
					}
					else {
						chosenLayer = 0x3;
					}
				}
				else {
					//Faron Woods
					stageComparison = strcmp(stageName, "F_SP108");
					if (stageComparison == 0) 
					{
						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xD4); //Can Transform at Will
						if (condition == false) {
								condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x602); //Forest Temple Completed
								if (condition == false) {
									condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4510); //Talo Saved
									if (condition == false) {
										chosenLayer = 0x1;
									}
								}
								else {
									chosenLayer = 0x2;
								}
							}
						else {
							chosenLayer = 0x5;
						}
					}
					else {
						//Coro's Lantern Shop
						stageComparison = strcmp(stageName, "R_SP108");
						if (stageComparison == 0) {
							condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x37]); //Forest Temple Completed
							if (condition == false) {
								condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4510); //Talo Saved
								if (condition == false) {
									chosenLayer = 0x1;
								}
							}
							else {
								chosenLayer = 0x2;
							}
						}
						else {
							//Kakariko Village / Kakariko Graveyard
							stageComparison = strcmp(stageName, "F_SP109");
							if ((stageComparison == 0) || (stageComparison = strcmp(stageName, "F_SP111"), stageComparison == 0)) {
								condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x804); //Got Zora Armor from Rutela
								if (condition == false) {
									condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x810); //Zora Escort Cleared
									if (condition == false) {
										condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x1320); //Cutscene after GM Watched
										if (condition == false) {
											condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x701); //Goron Mines Completed
											if (condition == false) {
												condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xa08); //KB1 Beaten
												if (condition == false) {
													condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x608); //KB1 Trigger Tripped
													if (condition != false) {
														chosenLayer = 0x1;
													}
												}
												else {
													chosenLayer = 0x2;
													//If it is night, the layer is different.
													libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
												}
											}
											else {
												chosenLayer = 0xc;
											}
										}
										else {
											chosenLayer = 0x2;
											libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
										}
									}
									else {
										chosenLayer = 0x4;
									}
								}
								else {
									chosenLayer = 0x2;
									libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
								}
							}
							else {
								//Kakariko Interiors
								stageComparison = strcmp(stageName, "R_SP109");
								if ((stageComparison == 0) || (stageComparison = strcmp(stageName, "R_SP209"), stageComparison == 0)) 
								{
									stageComparison = strcmp(stageName, "R_SP109");
									if ((stageComparison == 0) && ((roomId == 1 && (condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x904), condition != false)))) //Lakebed Completed
									{
										chosenLayer = 0x4;
										libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
									}
									else {
										condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x55]); //KB1 Beaten
										if (condition == false) {
											condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x35]); //KB1 Trigger Tripped
											if (condition != false) {
												chosenLayer = 0x1;
											}
										}
										else {
											chosenLayer = 0x2;
											libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
										}
									}
								}
								else {
									//Death Mountain
									stageComparison = strcmp(stageName, "F_SP110");
									if (stageComparison == 0) {
										condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x40]); //Goron Mines Completed
										if (condition != false) {
											chosenLayer = 0x2;
										}
									}
									else {
										//Death Mountain Sumo Hall
										stageComparison = strcmp(stageName, "R_SP110");
										if (stageComparison == 0) {
											condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2320); //Ilia shown Horse Call
											if (condition == false) {
												condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2004); //Temple of Time Completed
												if (condition == false) {
													condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2020); //Master Sword Story Progression Flag
													if (condition == false) {
														condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x701); //Goron Mines Completed
														if (condition != false) {
															chosenLayer = 0x1;
														}
													}
													else {
														chosenLayer = 0x2;
													}
												}
												else {
													chosenLayer = 0x4;
												}
											}
											else {
												chosenLayer = 0x3;
											}
										}
										else {
											//Lake Hylia
											stageComparison = strcmp(stageName, "F_SP115");
											if ((((stageComparison == 0) || (stageComparison = strcmp(stageName, "F_SP116"), stageComparison == 0)) ||
												((stageComparison = strcmp(stageName, "R_SP116"), stageComparison == 0 && (roomId == 5)))) ||
												(stageComparison = strcmp(stageName, "R_SP115"), stageComparison == 0)) {
												stageComparison = strcmp(stageName, "F_SP115");
												if ((stageComparison == 0) && (roomId == 0)) {
													condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x3b08); //Sky Cannon Repaired
													if (condition == false) {
														condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x3120); //Sky Cannon Warped to Lake Hylia
														if (condition == false) {
															condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x904); //Lakebed Temple Completed
															if (condition != false) {
																chosenLayer = 0x2;
															}
														}
														else {
															chosenLayer = 0x1;
														}
													}
													else {
														chosenLayer = 0x3;
													}
												}
												else {
													//Hyrule Castle Town Interiors
													stageComparison = strcmp(stageName, "R_SP116");
													if ((stageComparison == 0) &&
														((roomId == 5 &&
														(condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2020), condition != false //Master Sword Story Progression Flag
															)))) {
														chosenLayer = 0x4;
													}
													else {
														condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x1e08); //MDH Completed
														if ((condition == false) || (stageComparison = strcmp(stageName, "F_SP116"), stageComparison != 0))
														{
															condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x904); //Lakebed Temple Completed
															if (condition == false) {
																stageComparison = strcmp(stageName, "F_SP116");
																if (((stageComparison == 0) && (roomId == 3)) &&
																	(condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x44]), //Zora Escort Cleared
																		condition != false)) {
																	chosenLayer = 0x1;
																}
															}
															else {
																stageComparison = strcmp(stageName, "F_SP115");
																if (((stageComparison == 0) && (roomId == 1)) &&
																	(condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xc01), //MDH has been started
																		condition == false)) {
																	chosenLayer = 0x9;
																}
																else {
																	chosenLayer = 0x2;
																}
															}
														}
														else {
															if (((roomId == 4) || (roomId == 3)) || (roomId == 1)) {
																chosenLayer = 0x1;
															}
															else {
																chosenLayer = 0x0;
															}
														}
													}
												}
											}
											else {
												stageComparison = strcmp(stageName, "F_SP113");
												if (stageComparison == 0) {
													condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2008); //Snowpeak Ruins Completed
													if (condition != false) {
														chosenLayer = 0x2;
													}
												}
												else {
													stageComparison = strcmp(stageName, "F_SP126");
													if (stageComparison == 0) {
														condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x5F]); //Iza 1 Unlocked
														if (condition != false) {
															chosenLayer = 0x1;
														}
													}
													else {
														stageComparison = strcmp(stageName, "F_SP124");
														if ((stageComparison == 0) && (roomId == 0)) {
															chosenLayer = 0x8;
															condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4008); //Have been to desert
															if (condition != false) {
																chosenLayer = 0x0;
															}
														}
														else {
															stageComparison = strcmp(stageName, "F_SP112");
															if (stageComparison == 0) {
																condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xb01); //Iza 1 Minigame Completed
																if (condition == false) {
																	condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x902); //Iza 1 Minigame Started
																	if (condition != false) {
																		chosenLayer = 0x2;
																	}
																}
																else {
																	chosenLayer = 0x1;
																}
															}
															else {
																stageComparison = strcmp(stageName, "F_SP103");
																if (stageComparison == 0) {
																	if (roomId == 0) {
																		condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x38]); //Epona Tamed
																		if (condition == false) {
																			uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																			if (uVar2 == 0) {
																				condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x2F]); //First Trip to Sewers Done
																				if (condition == false) {
																					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4510); //Talo Saved
																					if (condition == false) {
																						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4a40); //Ordon Day 1 done
																						if (condition == false) {
																							chosenLayer = 0x6;
																						}
																						else {
																							chosenLayer = 0x0;
																						}
																					}
																					else {
																						chosenLayer = 0x7;
																					}
																				}
																				else {
																					chosenLayer = 0x1;
																				}
																			}
																			else {
																				chosenLayer = 0x2;
																				libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
																			}
																		}
																		else {
																			chosenLayer = 0x4;
																			libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
																		}
																	}
																	else {
																		if (roomId == 1) {
																			uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																			if (uVar2 == 0) {
																				condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x2F]); //First trip to Sewers done
																				if (condition == false) {
																					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4510); //Talo Saved
																					if (condition == false) {
																						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4a40); //Ordon Day 1 done
																						if (condition == false) {
																							chosenLayer = 0x3;
																						}
																						else {
																							chosenLayer = 0x4;
																						}
																					}
																					else {
																						chosenLayer = 0x0;
																					}
																				}
																				else {
																					chosenLayer = 0x1;
																				}
																			}
																			else {
																				chosenLayer = 0x2;
																			}
																		}
																	}
																}
																else {
																	stageComparison = strcmp(stageName, "R_SP01");
																	if (stageComparison == 0) {
																		if (roomId == 1) {
																			uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																			if (uVar2 != 0) {
																				chosenLayer = 0x2;
																			}
																		}
																		else {
																			if (roomId == 2) {
																				condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x780); //Watched Colin CS after KB1
																				if (condition == false) {
																					uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																					if (uVar2 == 0) {
																						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x2F]); //First Trip to Sewers done
																						if (condition != false) {
																							chosenLayer = 0x1;
																						}
																					}
																					else {
																						chosenLayer = 0x2;
																					}
																				}
																				else {
																					chosenLayer = 0x3;
																				}
																			}
																			else {
																				if (roomId == 5) {
																					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x601); //Epona Tamed
																					if (condition == false) {
																						uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																						if (uVar2 != 0) {
																							chosenLayer = 0x2;
																						}
																					}
																					else {
																						chosenLayer = 0x4;
																					}
																				}
																			}
																		}
																	}
																	else {
																		stageComparison = strcmp(stageName, "F_SP104");
																		if (stageComparison == 0) {
																			if (roomId == 1) {
																				uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																				if (uVar2 == 0) {
																					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x2F]); //First trip to Sewers done
																					if (condition == false) {
																						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4510); //Talo saved
																						if (condition == false) {
																							condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4a20); //Sword training done on Ordon Day 2
																							if (condition == false) {
																								chosenLayer = 0x1;
																							}
																							else {
																								chosenLayer = 0x3;
																							}
																						}
																						else {
																							chosenLayer = 0x0;
																						}
																					}
																					else {
																						chosenLayer = 0x4;
																					}
																				}
																				else {
																					chosenLayer = 0x2;
																				}
																			}
																			else {
																				uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																				if (uVar2 == 0) {
																					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x2F]); //First trip to Sewers done
																					if (condition != false) {
																						chosenLayer = 0x4;
																					}
																				}
																				else {
																					chosenLayer = 0x2;
																				}
																			}
																		}
																		else {
																			stageComparison = strcmp(stageName, "F_SP00");
																			if (stageComparison == 0) {
																				uVar2 = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
																				if (uVar2 == 0) {
																					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x2F]); //First trip to Sewers done
																					if (condition == false) {
																						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0xA9]); //Saw CS after Goats 2 done
																						if (condition == false) {
																							condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4510); //Talo Saved
																							if (condition == false) {
																								condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4a40); //Day 1 done
																								if (condition == false) {
																									chosenLayer = 0xc;
																								}
																								else {
																									chosenLayer = 0xb;
																								}
																							}
																							else {
																								chosenLayer = 0x9;
																							}
																						}
																						else {
																							chosenLayer = 0xa;
																						}
																					}
																					else {
																						chosenLayer = 0x1;
																					}
																				}
																				else {
																					chosenLayer = 0x2;
																					libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
																				}
																			}
																			else {
																				stageComparison = strcmp(stageName, "F_SP121");
																				if (stageComparison == 0) {
																					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x1e08); //MDH Completed
																					if (condition == false) {
																						condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xc01); //MDH State Activated
																						if (condition == false) {
																							condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x44]); //Zora Escort Cleared
																							if (condition == false) {
																								condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x601); //Epona Tamed
																								if (condition != false) {
																									condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x602); //Forest Temple Completed
																									if (condition == false) {
																										chosenLayer = 0x3;
																									}
																									else {
																										chosenLayer = 0x2;
																									}
																								}
																							}
																							else {
																								chosenLayer = 0x0;
																							}
																						}
																						else {
																							chosenLayer = 0x4;
																						}
																					}
																					else {
																						chosenLayer = 0x6;
																					}
																				}
																				else {
																					stageComparison = strcmp(stageName, "F_SP122");
																					if (stageComparison == 0) {
																						if (roomId == 8) {
																							condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x1e08); //MDH Completed
																							if (condition == false) {
																								condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xc01); //MDH State Activated
																								if (condition != false) {
																									chosenLayer = 0x4;
																								}
																							}
																							else {
																								chosenLayer = 0x6;
																							}
																						}
																						else {
																							if (roomId == 0x10) {
																								condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2204); //Wooden Statue Gotten
																								if (condition == false) {
																									condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2102); //Talked to Louise after Medicine Scent
																									if (condition == false) {
																										condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x1e08); //MDH Completed
																										if (condition == false) {
																											condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xc01); //MDH State Activated
																											if (condition != false) {
																												chosenLayer = 0x4;
																											}
																										}
																										else {
																											chosenLayer = 0x6;
																										}
																									}
																									else {
																										chosenLayer = 0x1;
																									}
																								}
																								else {
																									chosenLayer = 0x6;
																								}
																							}
																							else {
																								if (roomId == 0x11) {
																									condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x1e08); //MDH Completed
																									if (condition == false) {
																										condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xc01); //MDH State Activated
																										if (condition != false) {
																											chosenLayer = 0x4;
																										}
																									}
																									else {
																										chosenLayer = 0x0;
																									}
																								}
																							}
																						}
																					}
																					else {
																						stageComparison = strcmp(stageName, "F_SP128");
																						if (stageComparison == 0) {
																							condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2320); //Ilia shown Ilia's Charm
																							if (condition != false) {
																								chosenLayer = 0x1;
																							}
																						}
																						else {
																							stageComparison = strcmp(stageName, "R_SP160");
																							if (stageComparison == 0) {
																								if (roomId == 5) {
																									condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x1e08); //MDH Completed
																									if (condition == false) {
																										chosenLayer = 0x1;
																									}
																									else {
																										chosenLayer = 0x0;
																									}
																								}
																								else {
																									condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x2210); //CT Shop is Malo Mart
																									if (condition != false) {
																										chosenLayer = 0x1;
																									}
																								}
																							}
																							else {
																								stageComparison = strcmp(stageName, "F_SP117");
																								if (stageComparison == 0) {
																									chosenLayer = 0x2;
																								}
																								else {
																									//Bublin Camp
																									stageComparison = strcmp(stageName, "F_SP118");
																									if (stageComparison == 0) {
																										condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0xb40); //Escaped Burning Tent in Bublin Camp
																										if (condition != false) {
																											chosenLayer = 0x3;
																										}
																									}
																									else {
																										stageComparison = strcmp(stageName, "D_SB10");
																										if (stageComparison == 0) {
																											condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4510); //Talo saved
																											if (condition != false) {
																												chosenLayer = 0x1;
																											}
																										}
																										else {
																											stageComparison = strcmp(stageName, "R_SP107");
																											if (stageComparison == 0) {
																												stageComparison = libtp::tp::d_save::isTransformLV(playerStatusBPtr, 3); //Midna on Back
																												if (stageComparison != 0) {
																													chosenLayer = 0xd;
																												}
																											}
																											else {
																												stageComparison = strcmp(stageName, "D_MN09");
																												if (stageComparison == 0) {
																													if (((roomId != 0xb) && (roomId != 0xd)) &&
																														(roomId != 0xe)) {
																														chosenLayer = 0x1;
																													}
																												}
																												else {
																													stageComparison = strcmp(stageName, "F_SP127");
																													if ((stageComparison == 0) ||
																														(stageComparison = strcmp(stageName, "R_SP127"),
																															stageComparison == 0)) {
																														if (libtp::tp::d_kankyo::env_light.unk_98d[0x971] == 3) {
																															chosenLayer = 0x2;
																														}
																														else {
																															if (libtp::tp::d_kankyo::env_light.unk_98d[0x971] < 3) {
																																if (libtp::tp::d_kankyo::env_light.unk_98d[0x971] == 1) {
																																	chosenLayer = 0x0;
																																}
																																else {
																																	if (libtp::tp::d_kankyo::env_light.unk_98d[0x971] != 0) {
																																		chosenLayer = 0x1;
																																	}
																																}
																															}
																															else {
																																if (libtp::tp::d_kankyo::env_light.unk_98d[0x971] < 5) {
																																	chosenLayer = 0x3;
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (chosenLayer == 0xE) {
			condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(libtp::tp::d_save::saveBitLabels[0x41]); //Warped meteor to Zora's Domain
			if ((condition != false) &&
				((((stageComparison = strcmp(stageName, "F_SP112"), stageComparison == 0 ||
				(stageComparison = strcmp(stageName, "F_SP113"), stageComparison == 0)) ||
					((stageComparison = strcmp(stageName, "F_SP115"), stageComparison == 0 ||
					(stageComparison = strcmp(stageName, "F_SP116"), stageComparison == 0)))) ||
						(((stageComparison = strcmp(stageName, "R_SP116"), stageComparison == 0 && (roomId == 5)) ||
					((stageComparison = strcmp(stageName, "R_SP115"), stageComparison == 0 ||
							(((stageComparison = strcmp(stageName, "F_SP121"), stageComparison == 0 ||
						(stageComparison = strcmp(stageName, "F_SP126"), stageComparison == 0)) ||
								(stageComparison = strcmp(stageName, "F_SP122"), stageComparison == 0)))))))))) {
				stageComparison = strcmp(stageName, "F_SP121");
				if (stageComparison == 0) {
					if ((8 < roomId) && (roomId < 0xf)) {
						chosenLayer = 0xD;
					}
				}
				else {
					chosenLayer = 0xD;
				}
			}
			stageComparison = strcmp(stageName, "R_SP107");
			if ((stageComparison == 0) && (roomId == 0)) {
				condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x4d08); //Watched CS after being captured in Faron Twilight
				if (condition == false) {
					chosenLayer = 0xb;
				}
			}
			else {
				//Zant Boss Room
				stageComparison = strcmp(stageName, "D_MN08A");
				if ((stageComparison == 0) && (roomId == 10)) {
					condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(0x5410); //Zant Defeated
					if (condition == false) {
						chosenLayer = 0x0;
					}
					else {
						chosenLayer = 0x1;
					}
				}
			}
		}
		return chosenLayer;
	}
}     // namespace mod::game_patch