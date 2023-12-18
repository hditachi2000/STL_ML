#ifndef UUID2162286549712
#define UUID2162286549712

/**
  * RandomForestClassifier(base_estimator=deprecated, bootstrap=True, ccp_alpha=0.0, class_name=RandomForestClassifier, class_weight=None, criterion=gini, estimator=DecisionTreeClassifier(), estimator_params=('criterion', 'max_depth', 'min_samples_split', 'min_samples_leaf', 'min_weight_fraction_leaf', 'max_features', 'max_leaf_nodes', 'min_impurity_decrease', 'random_state', 'ccp_alpha'), max_depth=10, max_features=sqrt, max_leaf_nodes=None, max_samples=None, min_impurity_decrease=0.0, min_samples_leaf=1, min_samples_split=2, min_weight_fraction_leaf=0.0, n_estimators=5, n_jobs=None, num_outputs=3, oob_score=False, package_name=everywhereml.sklearn.ensemble, random_state=None, template_folder=everywhereml/sklearn/ensemble, verbose=0, warm_start=False)
 */
class RandomForestClassifier {
    public:

        /**
         * Predict class from features
         */
        int predict(float *x) {
            int predictedValue = 0;
            size_t startedAt = micros();

            
                    
            uint16_t votes[3] = { 0 };
            uint8_t classIdx = 0;
            float classScore = 0;

            
                tree0(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree1(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree2(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree3(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree4(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            

            // return argmax of votes
            uint8_t maxClassIdx = 0;
            float maxVote = votes[0];

            for (uint8_t i = 1; i < 3; i++) {
                if (votes[i] > maxVote) {
                    maxClassIdx = i;
                    maxVote = votes[i];
                }
            }

            predictedValue = maxClassIdx;

                    

            latency = micros() - startedAt;

            return (lastPrediction = predictedValue);
        }

        
            

            /**
             * Predict class label
             */
            String predictLabel(float *x) {
                return getLabelOf(predict(x));
            }

            /**
             * Get label of last prediction
             */
            String getLabel() {
                return getLabelOf(lastPrediction);
            }

            /**
             * Get label of given class
             */
            String getLabelOf(int8_t idx) {
                switch (idx) {
                    case -1:
                        return "ERROR";
                    
                        case 0:
                            return "background";
                    
                        case 1:
                            return "phuoc";
                    
                        case 2:
                            return "viet";
                    
                    default:
                        return "UNKNOWN";
                }
            }


            /**
             * Get latency in micros
             */
            uint32_t latencyInMicros() {
                return latency;
            }

            /**
             * Get latency in millis
             */
            uint16_t latencyInMillis() {
                return latency / 1000;
            }
            

    protected:
        float latency = 0;
        int lastPrediction = 0;

        
            

        
            
                /**
                 * Random forest's tree #0
                 */
                void tree0(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[74] < 0.0002893478376790881) {
                            
                                
                        if (x[95] < 0.12446184456348419) {
                            
                                
                        if (x[80] < 0.02590059646172449) {
                            
                                
                        if (x[72] < 0.04406420513987541) {
                            
                                
                        *classIdx = 0;
                        *classScore = 72.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 72.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[21] < 0.00973118469119072) {
                            
                                
                        if (x[28] < 0.003173146629706025) {
                            
                                
                        *classIdx = 1;
                        *classScore = 93.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[70] < 0.013145525008440018) {
                            
                                
                        if (x[0] < 0.1330852210521698) {
                            
                                
                        if (x[121] < 0.10211170092225075) {
                            
                                
                        if (x[57] < 0.058001527562737465) {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 93.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[88] < 0.05184890888631344) {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 93.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[12] < 0.0362286064773798) {
                            
                                
                        if (x[97] < 0.4725211262702942) {
                            
                                
                        if (x[26] < 0.022927042096853256) {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 93.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[58] < 0.07077083550393581) {
                            
                                
                        if (x[35] < 0.17025314271450043) {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 93.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[16] < 0.8029677271842957) {
                            
                                
                        *classIdx = 1;
                        *classScore = 93.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #1
                 */
                void tree1(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[99] < 0.11730049178004265) {
                            
                                
                        if (x[104] < 0.0017891067545861006) {
                            
                                
                        *classIdx = 0;
                        *classScore = 73.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[63] < 0.41084179282188416) {
                            
                                
                        if (x[10] < 0.24786009639501572) {
                            
                                
                        if (x[120] < 0.7264849543571472) {
                            
                                
                        if (x[108] < 0.26327718049287796) {
                            
                                
                        *classIdx = 1;
                        *classScore = 92.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[20] < 0.1927679106593132) {
                            
                                
                        *classIdx = 1;
                        *classScore = 92.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[0] < 0.13754737004637718) {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 92.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[99] < 0.0074703998398035765) {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 92.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[118] < 0.0008227351936511695) {
                            
                                
                        if (x[34] < 0.12569774687290192) {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[107] < 0.020397996995598078) {
                            
                                
                        *classIdx = 0;
                        *classScore = 73.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 97.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #2
                 */
                void tree2(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[12] < 0.15436716377735138) {
                            
                                
                        if (x[11] < 0.014411647338420153) {
                            
                                
                        if (x[89] < 0.006352927070111036) {
                            
                                
                        if (x[34] < 0.014924255199730396) {
                            
                                
                        *classIdx = 2;
                        *classScore = 90.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[0] < 0.07688972726464272) {
                            
                                
                        if (x[8] < 0.5497105717658997) {
                            
                                
                        *classIdx = 2;
                        *classScore = 90.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[100] < 0.07096774131059647) {
                            
                                
                        if (x[24] < 0.02083997568115592) {
                            
                                
                        *classIdx = 2;
                        *classScore = 90.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[91] < 0.0836823582649231) {
                            
                                
                        *classIdx = 2;
                        *classScore = 90.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 77.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[74] < 0.0026829608250409365) {
                            
                                
                        *classIdx = 0;
                        *classScore = 77.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[14] < 0.3799666464328766) {
                            
                                
                        *classIdx = 2;
                        *classScore = 90.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #3
                 */
                void tree3(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[89] < 0.79376620054245) {
                            
                                
                        if (x[99] < 0.11187471821904182) {
                            
                                
                        if (x[109] < 0.1445092037320137) {
                            
                                
                        if (x[133] < 0.019092775881290436) {
                            
                                
                        *classIdx = 2;
                        *classScore = 103.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[72] < 0.9623916149139404) {
                            
                                
                        *classIdx = 1;
                        *classScore = 81.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[13] < 0.046088580042123795) {
                            
                                
                        *classIdx = 1;
                        *classScore = 81.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 103.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[24] < 0.19249887019395828) {
                            
                                
                        *classIdx = 2;
                        *classScore = 103.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 81.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[0] < 0.23751422762870789) {
                            
                                
                        *classIdx = 2;
                        *classScore = 103.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[74] < 0.022864393889904022) {
                            
                                
                        *classIdx = 0;
                        *classScore = 78.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 103.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[98] < 0.31087837740778923) {
                            
                                
                        *classIdx = 0;
                        *classScore = 78.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 81.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #4
                 */
                void tree4(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[101] < 0.3303966671228409) {
                            
                                
                        if (x[88] < 0.06081616133451462) {
                            
                                
                        if (x[120] < 0.04405190795660019) {
                            
                                
                        if (x[131] < 0.28773052245378494) {
                            
                                
                        if (x[98] < 0.3294563442468643) {
                            
                                
                        *classIdx = 0;
                        *classScore = 75.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 92.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[130] < 0.051921240985393524) {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[41] < 0.2910628691315651) {
                            
                                
                        *classIdx = 2;
                        *classScore = 92.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[33] < 0.49405233561992645) {
                            
                                
                        if (x[112] < 0.7304239869117737) {
                            
                                
                        if (x[45] < 0.3787948787212372) {
                            
                                
                        if (x[60] < 0.00343331485055387) {
                            
                                
                        if (x[14] < 0.008970680646598339) {
                            
                                
                        *classIdx = 2;
                        *classScore = 92.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 95.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 92.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[87] < 0.2746153101325035) {
                            
                                
                        *classIdx = 2;
                        *classScore = 92.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[24] < 0.006353392731398344) {
                            
                                
                        *classIdx = 2;
                        *classScore = 92.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 0;
                        *classScore = 75.0;
                        return;

                            
                        }

                            
                        }

                }
            
        


            
};



static RandomForestClassifier classifier;


#endif