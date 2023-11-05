// OpenAI, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Provider/ResponseTypes.h"
#include "Provider/RequestTypes.h"
#include "ListFineTuningJobsAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnListFineTuningJobs, const FListFineTuningJobsResponse&, Response, const FOpenAIError&, RawError);

class UOpenAIProvider;

UCLASS()
class UListFineTuningJobsAction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnListFineTuningJobs OnCompleted;

    virtual void Activate() override;

private:
    /**
     * @param URLOverride Allows for the specification of a custom endpoint. This is beneficial when using a proxy.
     * If this functionality is not required, this parameter can be left blank.
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "OpenAI | FineTunes")
    static UListFineTuningJobsAction* ListFineTuningJobs(
        const FFineTuningQueryParameters& FineTuningQueryParameters, const FOpenAIAuth& Auth, const FString& URLOverride);

    void TryToOverrideURL(UOpenAIProvider* Provider);

    void OnListFineTuningJobsCompleted(const FListFineTuningJobsResponse& Response);
    void OnRequestError(const FString& URL, const FString& Content);

private:
    FFineTuningQueryParameters FineTuningQueryParameters;
    FOpenAIAuth Auth;
    FString URLOverride{};
};
